// request.hpp
// (C) Martin Alebachew, 2023

/*
This file defines the KMS request wrapper struct.
This file includes modified code from vlmcsd/kms.h by Wind4.
*/

#pragma once
#include "winapi_types.hpp"
#include "crypto.hpp"
#include "sha256.hpp"
#include <vector>

struct VERSION {
  WORD Minor;
  WORD Major;
} __attribute__((packed)); // Disabling compiler alignment in favor of RPC alignment.

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
  GUID AppID;                // Can currently be Windows, Office2010 or Office2013
  GUID ActID;                // aka SKUID. Most detailed product list. One product key per ActID. Ignored by KMS server
  GUID KMSID;                // This is what the KMS server uses to grant or refuse activation
  GUID CMID;                 // Client machine Id. Used by the KMS server for counting minimum clients
  DWORD N_Policy;            // Minimum clients required for activation
  FILETIME ClientTime;       // Current client time
  GUID CMID_prev;            // Previous client machine Id. All zeros, if it never changed
  WCHAR WorkstationName[64]; // Workstation name. FQDN if available, NetBIOS otherwise
  BYTE Pad[4];               // Fixed padding (request size is fixed, required for AES, PKCS7)  

  Request(std::vector<byte> stub);
  std::string GetWorkstationName();
} __attribute__((packed)); // Disabling compiler alignment in favor of RPC alignment.
} // namespace KMS