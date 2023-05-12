// winapi_types.hpp
// (C) Martin Alebachew, 2023

/*
This file defines the WinAPI types required for KMS.
*/

#pragma once
#include <cstdint>

typedef u_int16_t WORD;
typedef u_int32_t DWORD;
typedef char16_t WCHAR;
typedef unsigned char byte;
typedef byte BYTE;

struct GUID {
  u_int32_t Data1;
  u_int16_t Data2;
  u_int16_t Data3;
  byte Data4[8];

  std::string toString() {
    char guid_cstr[37];
    snprintf(guid_cstr, sizeof(guid_cstr),
             "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x", Data1, Data2,
             Data3, Data4[0], Data4[1], Data4[2], Data4[3], Data4[4], Data4[5],
             Data4[6], Data4[7]);

    return std::string(guid_cstr);
  }
} __attribute__((
    packed)); // Disabling compiler alignment in favor of RPC alignment.

struct FILETIME {
  DWORD dwLowDateTime;
  DWORD dwHighDateTime;
} __attribute__((
    packed)); // Disabling compiler alignment in favor of RPC alignment.
