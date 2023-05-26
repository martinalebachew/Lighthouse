// crypto.hpp
// (C) Martin Alebachew, 2023

/*
This file contains modified Wind4/vlmcsd implementations of AES.
*/

#pragma once
#include "winapi_types.hpp"
#include <cstdint>
#include <cstring>
#include <bit>

#define AES_BLOCK_BYTES (16)
#define AES_BLOCK_WORDS (AES_BLOCK_BYTES / sizeof(DWORD))

#define ROR32(v, n) ( (v) << (32 - n) | (v) >> n )

typedef struct {
	DWORD Key[48]; // Supports a maximum of 160 key bits!
	uint_fast8_t rounds;
} AesCtx;

const std::vector<BYTE> KeyV6 = {	0xA9, 0x4A, 0x41, 0x95, 0xE2, 0x01, 0x43, 0x2D, 0x9B, 0xCB, 0x46, 0x04, 0x05, 0xD8, 0x4A, 0x21 };

void XorBlock(const BYTE *const in, const BYTE *out);

#define rand32() ((uint32_t)((rand() << 17) | (rand() << 2) | (rand() & 3)))
void get16RandomBytes(void* ptr);

#define AddRoundKey(d, rk) XorBlock((const BYTE *)rk, (const BYTE *)d)

#define Mul2(word) (((word & 0x7f7f7f7f) << 1) ^ (((word & 0x80808080) >> 7) * 0x1b))
#define Mul3(word) (Mul2(word) ^ word)
#define Mul4(word) (Mul2(Mul2(word)))
#define Mul8(word) (Mul2(Mul2(Mul2(word))))
#define Mul9(word) (Mul8(word) ^ word)
#define MulB(word) (Mul8(word) ^ Mul3(word))
#define MulD(word) (Mul8(word) ^ Mul4(word) ^ word)
#define MulE(word) (Mul8(word) ^ Mul4(word) ^ Mul2(word))


void MixColumnsR(BYTE* __restrict__ state);
void AesInitKey(AesCtx *Ctx, std::vector<BYTE> key);
void AesEncryptBlock(const AesCtx *const Ctx, BYTE *block);

#define GetSBoxR(x) SBoxR[x]

void AesEncryptCbc(const AesCtx *const Ctx, BYTE* __restrict__ data, size_t* __restrict__ len);
void AesDecryptBlock(const AesCtx *const Ctx, BYTE *block);
void AesDecryptCbc(const AesCtx *const Ctx, BYTE *data, size_t len);