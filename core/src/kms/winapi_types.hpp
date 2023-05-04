// winapi_types.hpp
// (C) Martin Alebachew, 2023

/*
This file defines the WinAPI types required for KMS.
*/

#pragma once

typedef unsigned short WORD;
typedef unsigned long DWORD;

typedef unsigned char byte;
typedef byte BYTE;

typedef wchar_t WCHAR;

struct GUID {
  unsigned long Data1;
  unsigned short Data2;
  unsigned short Data3;
  unsigned char Data4[8];
};

struct FILETIME {
  DWORD dwLowDateTime;
  DWORD dwHighDateTime;
};
