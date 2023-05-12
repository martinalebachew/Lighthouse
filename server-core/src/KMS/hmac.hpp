// hmac.hpp
// (C) Martin Alebachew, 2023

/*
This file contains modified Wind4/vlmcsd implementation of HMAC.
*/

#pragma once
#include "winapi_types.hpp"
#include "crypto.hpp"
#include "response.hpp"
#include <bit>

#define TIME_C1 0x00000022816889BDULL
#define TIME_C2 0x000000208CBAB5EDULL
#define TIME_C3 0x3156CD5AC628477AULL

struct PACKED64
{
	uint64_t val[0];
} __attribute__((packed));

#define GET_UA64LE(p) (((PACKED64*)p)->val[0])

typedef struct {
	Sha256Ctx  ShaCtx;
	BYTE  OPad[64];
} Sha256HmacCtx;

static void _Sha256HmacInit(Sha256HmacCtx *Ctx, BYTE *key, size_t klen)
{
	BYTE  IPad[64];
	unsigned int  i;

	memset(IPad, 0x36, sizeof(IPad));
	memset(Ctx->OPad, 0x5C, sizeof(Ctx->OPad));

	if ( klen > 64 )
	{
		BYTE *temp = (BYTE*)alloca(32);
		Sha256(key, klen, temp);
		klen = 32;
		key  = temp;
	}

	for (i = 0; i < klen; i++)
	{
		IPad[ i ]      ^= key[ i ];
		Ctx->OPad[ i ] ^= key[ i ];
	}

	Sha256Init(&Ctx->ShaCtx);
	Sha256Update(&Ctx->ShaCtx, IPad, sizeof(IPad));
}


static void _Sha256HmacUpdate(Sha256HmacCtx *Ctx, BYTE *data, size_t len)
{
	Sha256Update(&Ctx->ShaCtx, data, len);
}


static void _Sha256HmacFinish(Sha256HmacCtx *Ctx, BYTE *hmac)
{
	BYTE  temp[32];

	Sha256Finish(&Ctx->ShaCtx, temp);
	Sha256Init(&Ctx->ShaCtx);
	Sha256Update(&Ctx->ShaCtx, Ctx->OPad, sizeof(Ctx->OPad));
	Sha256Update(&Ctx->ShaCtx, temp, sizeof(temp));
	Sha256Finish(&Ctx->ShaCtx, hmac);
}



int_fast8_t Sha256Hmac(BYTE* key, BYTE* __restrict__ data, DWORD len, BYTE* __restrict__ hmac)
{
	Sha256HmacCtx Ctx;
	_Sha256HmacInit(&Ctx, key, 16);
	_Sha256HmacUpdate(&Ctx, data, len);
	_Sha256HmacFinish(&Ctx, hmac);
	return true;
}

/*
 * Creates the HMAC for v6
 */
static int_fast8_t CreateV6Hmac(BYTE *const encrypt_start, const size_t encryptSize, const int_fast8_t tolerance)
{
	BYTE hash[32];
	const uint8_t halfHashSize = sizeof(hash) >> 1;
	BYTE *responseEnd = encrypt_start + encryptSize;

  constexpr size_t V6_POST_EPID_SIZE = 124; // sizeof(KMS::Response) - offsetof(KMS::Response, CMID);

	// This is the time from the response
	FILETIME* ft = (FILETIME*)(responseEnd - V6_POST_EPID_SIZE + sizeof(GUID)); // sizeof(((KMS::Response*)0)->CMID)

	// Generate a time slot that changes every 4.11 hours.
	// Request and response time must match +/- 1 slot.
	// When generating a response tolerance must be 0.
	// If verifying the hash, try tolerance -1, 0 and +1. One of them must match.

	uint64_t timeSlot = (GET_UA64LE(ft) / TIME_C1 * TIME_C2 + TIME_C3) + (tolerance * TIME_C1);

	// The time slot is hashed with SHA256 so it is not so obvious that it is time
	Sha256((BYTE*)&timeSlot, sizeof(timeSlot), hash);

	// The last 16 bytes of the hashed time slot are the actual HMAC key
	if (!Sha256Hmac
	(
		hash + halfHashSize,									// Use last 16 bytes of SHA256 as HMAC key
		encrypt_start,											// hash only the encrypted part of the v6 response
		(DWORD)(encryptSize - 16),	// encryptSize minus the HMAC itself, 16 bytes
		hash													// use same buffer for resulting hash where the key came from
	))
	{
		return false;
	}

	memcpy(responseEnd - 16, hash + halfHashSize, halfHashSize); // HMAC size is 16 bytes
	return true;
}