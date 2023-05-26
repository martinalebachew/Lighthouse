// winapi_types.cpp
// (C) Martin Alebachew, 2023

/*
This file defines the WinAPI types required for KMS.
*/

#include "winapi_types.hpp"

std::string GUID::toString() {
  char guid_cstr[37];
  snprintf(guid_cstr, sizeof(guid_cstr),
           "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x", Data1, Data2,
           Data3, Data4[0], Data4[1], Data4[2], Data4[3], Data4[4], Data4[5],
           Data4[6], Data4[7]);

  return std::string(guid_cstr);
}
