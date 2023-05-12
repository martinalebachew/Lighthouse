// winapi_types.hpp
// (C) Martin Alebachew, 2023

/*
This file defines the WinAPI types required for KMS.
*/

#pragma once
#include <cstdint>
#include <iostream>

typedef u_int16_t WORD;
typedef u_int32_t DWORD;
typedef char16_t WCHAR;
typedef unsigned char byte;
typedef byte BYTE;

struct GUID {
  u_int32_t Data1;
  u_int16_t Data2;
  u_int16_t Data3;
  byte      Data4[8];

  std::string toString();
} __attribute__((packed)); // Disabling compiler alignment in favor of RPC alignment.

struct FILETIME {
  DWORD dwLowDateTime;
  DWORD dwHighDateTime;
} __attribute__((packed)); // Disabling compiler alignment in favor of RPC alignment.