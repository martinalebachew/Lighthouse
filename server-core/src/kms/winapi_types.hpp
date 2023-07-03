// winapi_types.hpp
// (C) Martin Alebachew, 2023

/*
This file defines the WinAPI types required for KMS.
*/

#pragma once
#include <cstdint>
#include <iostream>

#pragma pack(1) // Required for RPC data layout

typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef char16_t WCHAR;
typedef unsigned char byte;
typedef byte BYTE;

struct GUID {
  uint32_t Data1;
  uint16_t Data2;
  uint16_t Data3;
  byte      Data4[8];

  std::string toString();
};

struct FILETIME {
  DWORD dwLowDateTime;
  DWORD dwHighDateTime;
};