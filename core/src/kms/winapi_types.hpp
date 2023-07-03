// winapi_types.hpp
// (C) Martin Alebachew, 2023

/*
This file defines the WinAPI types required for KMS.
*/

#pragma once
#pragma pack(push, 1)
#include <cstdint>
#include <cstdio>
#include <string>

typedef uint16_t WORD;
typedef uint32_t DWORD;

typedef unsigned char byte;
typedef byte BYTE;

typedef char16_t WCHAR;

struct GUID {
  uint32_t Data1;
  uint16_t Data2;
  uint16_t Data3;
  byte Data4[8];

  std::string toString();
};

struct FILETIME {
  DWORD dwLowDateTime;
  DWORD dwHighDateTime;
};

#pragma pack(pop)
