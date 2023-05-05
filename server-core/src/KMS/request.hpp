// request.hpp
// (C) Martin Alebachew, 2023

/*
This file defines the KMS request wrapper struct.
This file includes modified code from vlmcsd/kms.h by Wind4.
*/

#pragma once
#include "winapi_types.hpp"
#include "crypto.hpp"
#include <vector>

struct VERSION {
  WORD Minor;
  WORD Major;
} __attribute__((
    packed)); // Disabling compiler alignment in favor of RPC alignment.

namespace KMS {
struct Request {
  /* NOTE
     Modifying the properties below may break the casting algorithm.
     Adjust it accordingly.
  */

  /* Body length padding
     Contains the length of the properties after the padding, fixed value
     of 260 bytes == sizeof(Request) - offsetof(Request, RawVersion) */
  u_int32_t bodyLength1 = 260;
  u_int32_t bodyLength2 = 260;

  /* UNENCRYPTED */
  VERSION RawVersion; // Minor and major version, unencrypted
  BYTE IV[16];        // IV

  /* ENCRYPTED AES CBC 128-bits key, PKCS7 */
  VERSION Version;           // Minor and major version
  DWORD VMInfo;              // 0 = client is bare metal, 1 = client is VM
  DWORD LicenseStatus;       // 0 = Unlicensed, 1 = Licensed (Activated), 2 = OOB grace, 3 = OOT grace, 4 = NonGenuineGrace, 5 = Notification, 6 = extended grace
  DWORD BindingExpiration;   // Expiration of the current status in minutes (e.g. when KMS activation or OOB grace expires)
  GUID AppID;                // Can currently be Windows, Office2010 or Office2013 (see kms.c, table AppList)
  GUID ActID;                // Most detailed product list. One product key per ActID. Ignored by KMS server
  GUID KMSID;                // This is what the KMS server uses to grant or refuse activation
  GUID CMID;                 // Client machine Id. Used by the KMS server for counting minimum clients
  DWORD N_Policy;            // Minimum clients required for activation
  FILETIME ClientTime;       // Current client time
  GUID CMID_prev;            // Previous client machine Id. All zeros, if it never changed
  WCHAR WorkstationName[64]; // Workstation name. FQDN if available, NetBIOS otherwise
  BYTE Pad[4];               // Fixed padding (request size is fixed, required for AES, PKCS7)  

  inline Request(std::vector<byte> stub)
  {
    // Validate stub size
    if (stub.size() != sizeof(Request))
      throw std::runtime_error("Invalid stub size. Expected " +
                                std::to_string(sizeof(Request)) + " bytes, got " +
                                std::to_string(stub.size()) + " bytes.");

    // Copy all properties
    memcpy(this, stub.data(), sizeof(Request));

    // Decrypt stub encrypted properties
    AesCtx ctx;
    AesInitKey(&ctx, AesKeyV6, 16);
    AesDecryptCbc(&ctx, NULL, IV, 256);

    // Validate decryption
    if (!!memcmp(&RawVersion, &Version, sizeof(VERSION))) 
      throw std::runtime_error("Stub decryption failed.");
  }

  inline std::string GetWorkstationName() {
    std::string name = "";
    for (int i = 0; i < 64; i++) {
      if (WorkstationName[i] == 0) break;
      name += WorkstationName[i];
    }

    return name;
  }
} __attribute__((
    packed)); // Disabling compiler alignment in favor of RPC alignment.
} // namespace KMS