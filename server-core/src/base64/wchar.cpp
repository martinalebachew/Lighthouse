// wchar.cpp
// (C) Martin Alebachew

#include "wchar.hpp"

std::string wcharStringToBase64(WCHAR *string, size_t length) {
  size_t terminatorOffset = 0;
  for (; terminatorOffset < length; terminatorOffset++) {
    // Find the offset of the null-terminator wchar in string
    if (*(int16_t*)&string[terminatorOffset] == 0) break;
  }

  return base64_encode((unsigned char*)string, terminatorOffset * sizeof(WCHAR));
}