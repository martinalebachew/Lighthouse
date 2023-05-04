// winapi_types.hpp
// (C) Martin Alebachew, 2023

/*
This file defines the WinAPI types required for KMS.
*/

#pragma once
#include <cstdint>

typedef u_int16_t WORD;
typedef u_int32_t DWORD;

struct GUID {
  unsigned long  Data1;
  unsigned short Data2;
  unsigned short Data3;
  unsigned char  Data4[8];
} __attribute__((
    packed)); // Disabling compiler alignment in favor of RPC alignment.

typedef char16_t WCHAR;
typedef unsigned char byte;
typedef byte BYTE;

struct FILETIME {
  DWORD dwLowDateTime;
  DWORD dwHighDateTime;
} __attribute__((
    packed)); // Disabling compiler alignment in favor of RPC alignment.