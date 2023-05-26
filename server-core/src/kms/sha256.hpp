// sha256.hpp
// (C) Martin Alebachew, 2023

/*
This file contains modified Wind4/vlmcsd implementation of SHA256.
*/

#pragma once
#include "crypto.hpp"
#include "winapi_types.hpp"
#include <bit>
#include <cstring>

#define F0(x, y, z) (((x) & (y)) | (~(x) & (z)))
#define F1(x, y, z) (((x) & (y)) | ((x) & (z)) | ((y) & (z)))

#define SI1(x) (ROR32(x, 2) ^ ROR32(x, 13) ^ ROR32(x, 22))
#define SI2(x) (ROR32(x, 6) ^ ROR32(x, 11) ^ ROR32(x, 25))
#define SI3(x) (ROR32(x, 7) ^ ROR32(x, 18) ^ ((x) >> 3))
#define SI4(x) (ROR32(x, 17) ^ ROR32(x, 19) ^ ((x) >> 10))

typedef struct {
  DWORD State[8];
  BYTE Buffer[64];
  unsigned int Len;
} Sha256Ctx;

void Sha256Init(Sha256Ctx *Ctx);
void Sha256Update(Sha256Ctx *Ctx, BYTE *data, size_t len);
void Sha256Finish(Sha256Ctx *Ctx, BYTE *hash);
void Sha256(BYTE *data, size_t len, BYTE *hash);
