// hmac.hpp
// (C) Martin Alebachew, 2023

/*
This file contains modified Wind4/vlmcsd implementation of HMAC.
*/

#pragma once
#include "crypto.hpp"
#include "response.hpp"
#include "sha256.hpp"
#include "winapi_types.hpp"
#include <bit>

#define TIME_C1 0x00000022816889BDULL
#define TIME_C2 0x000000208CBAB5EDULL
#define TIME_C3 0x3156CD5AC628477AULL

struct PACKED64 {
  uint64_t val[0];
} __attribute__((packed));

#define GET_UA64LE(p) (((PACKED64*)p)->val[0])

typedef struct {
  Sha256Ctx ShaCtx;
  BYTE OPad[64];
} Sha256HmacCtx;

int_fast8_t Sha256Hmac(BYTE* key, BYTE* __restrict__ data, DWORD len, BYTE* __restrict__ hmac);
int_fast8_t CreateV6Hmac(
  BYTE* const encrypt_start, const size_t encryptSize, const int_fast8_t tolerance
);
