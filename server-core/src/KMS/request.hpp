// request.hpp
// (C) Martin Alebachew, 2023

/*
This file defines the KMS request wrapper struct.
This file includes modified code from vlmcsd/kms.h by Wind4.
*/

#pragma once
#include "winapi_types.hpp"
#include <vector>

typedef struct _VERSION {
  WORD Minor;
  WORD Major;
} VERSION;

namespace KMS {
struct Request {
  /* NOTE
     Modifying the properties below may break the casting algorithm.
     Adjust it accordingly.
  */

  /* UNENCRYPTED */
  VERSION RawVersion;     // Minor and major version, unencrypted
	BYTE IV[16];         // IV	

  /* ENCRYPTED */
  VERSION Version;           // Minor and major version
  DWORD VMInfo;              // 0 = client is bare metal, 1 = client is VM
  DWORD LicenseStatus;       // 0 = Unlicensed, 1 = Licensed (Activated), 2 = OOB grace, 3 = OOT grace, 4 = NonGenuineGrace, 5 = Notification, 6 = extended grace
  DWORD BindingExpiration;   // Expiration of the current status in minutes (e.g. when KMS activation or OOB grace expires)
  GUID AppID;                // Can currently be Windows, Office2010 or Office2013 (see kms.c, table AppList)
  GUID ActID;                // Most detailed product list. One product key per ActID (see kms.c, table ExtendedProductList). Is ignored by KMS server
  GUID KMSID;                // This is what the KMS server uses to grant or refuse activation (see kms.c, table BasicProductList)
  GUID CMID;                 // Client machine Id. Used by the KMS server for counting minimum clients
  DWORD N_Policy;            // Minimum clients required for activation
  FILETIME ClientTime;       // Current client time
  GUID CMID_prev;            // Previous client machine Id. All zeros, if it never changed
  WCHAR WorkstationName[64]; // Workstation name. FQDN if available, NetBIOS otherwise

  BYTE Pad[4]; // Fixed padding (request size is fixed, required for AES, PKCS)
};
}