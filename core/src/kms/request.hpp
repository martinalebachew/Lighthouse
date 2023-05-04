// request.hpp
// (C) Martin Alebachew, 2023

/*
This file defines the KMS Request struct.
This file includes modified code from vlmcsd/kms.h by Wind4.
*/

#pragma once
#include "winapi_types.hpp"
#include <vector>

struct VERSION {
  WORD Minor;
  WORD Major;
};

namespace KMS {
struct Request {
  /* NOTE
  Modifying the properties below may break the casting algorithm.
  Adjust it accordingly.
  */

  // UNENCRYPTED
  VERSION RawVersion; // Minor and major version, unencrypted
  BYTE IV[16];        // Initialization vector

  // ENCRYPTED, AES CBC 128-bits key, PKCS7
  VERSION Version;           // Minor and major version
  DWORD VMInfo;              // 0 = client is bare metal, 1 = client is VM
  DWORD LicenseStatus;       // 0 = Unlicensed, 1 = Licensed (Activated), 2 = OOB grace, 3 = OOT grace, 4 = NonGenuineGrace, 5 = Notification, 6 = extended grace
  DWORD BindingExpiration;   // Expiration of the current status in minutes (e.g. when KMS activation or OOB grace expires)
  GUID AppID;                // Can currently be Windows, Office2010 or Office2013
  GUID ActID;                // AKA SKUID. Most detailed product list. One product key per ActID. Ignored by KMS server
  GUID KMSID;                // This is what the KMS server uses to grant or refuse activation
  GUID CMID;                 // Client machine Id. Used by the KMS server for counting minimum clients
  DWORD N_Policy;            // Minimum clients required for activation
  FILETIME ClientTime;       // Current client time
  GUID CMID_prev;            // Previous client machine Id. All zeros, if it never changed
  WCHAR WorkstationName[64]; // Workstation name. FQDN if available, NetBIOS otherwise

  BYTE Pad[4]; // Fixed padding (request size is fixed, required for encryption)
};
} // namespace KMS
