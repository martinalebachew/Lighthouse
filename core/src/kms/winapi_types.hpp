// winapi_types.hpp
// (C) Martin Alebachew, 2023

/*
This file defines the WinAPI types required for KMS.
*/

#pragma once
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
} __attribute__((packed)); // Disabling compiler alignment in favor of RPC alignment

struct FILETIME {
  DWORD dwLowDateTime;
  DWORD dwHighDateTime;
} __attribute__((packed)); // Disabling compiler alignment in favor of RPC alignment
