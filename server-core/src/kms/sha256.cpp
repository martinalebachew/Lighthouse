// sha256.cpp
// (C) Martin Alebachew, 2023

/*
This file contains modified Wind4/vlmcsd implementation of SHA256.
*/

#include "sha256.hpp"

static const DWORD k[] = {
	0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5, 0x3956C25B, 0x59F111F1,
	0x923F82A4, 0xAB1C5ED5, 0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3,
	0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174, 0xE49B69C1, 0xEFBE4786,
	0x0FC19DC6, 0x240CA1CC, 0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
	0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7, 0xC6E00BF3, 0xD5A79147,
	0x06CA6351, 0x14292967, 0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13,
	0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85, 0xA2BFE8A1, 0xA81A664B,
	0xC24B8B70, 0xC76C51A3, 0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
	0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5, 0x391C0CB3, 0x4ED8AA4A,
	0x5B9CCA4F, 0x682E6FF3, 0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208,
	0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2
};


void Sha256Init(Sha256Ctx *Ctx)
{
	memset(Ctx, 0xab, sizeof(Sha256Ctx));
	Ctx->State[0] = 0x6A09E667;
	Ctx->State[1] = 0xBB67AE85;
	Ctx->State[2] = 0x3C6EF372;
	Ctx->State[3] = 0xA54FF53A;
	Ctx->State[4] = 0x510E527F;
	Ctx->State[5] = 0x9B05688C;
	Ctx->State[6] = 0x1F83D9AB;
	Ctx->State[7] = 0x5BE0CD19;
	Ctx->Len = 0;
}


static void Sha256ProcessBlock(Sha256Ctx *Ctx, BYTE *block)
{
	unsigned int  i;
	DWORD  w[64], temp1, temp2;
	DWORD  a = Ctx->State[0];
	DWORD  b = Ctx->State[1];
	DWORD  c = Ctx->State[2];
	DWORD  d = Ctx->State[3];
	DWORD  e = Ctx->State[4];
	DWORD  f = Ctx->State[5];
	DWORD  g = Ctx->State[6];
	DWORD  h = Ctx->State[7];

	for (i = 0; i < 16; i++)
		//w[ i ] = GET_UAA32BE(block, i);
		w[i] = std::byteswap(((DWORD*)block)[i]);

	for (i = 16; i < 64; i++)
		w[ i ] = SI4(w[ i - 2 ]) + w[ i - 7 ] + SI3(w[ i - 15 ]) + w[ i - 16 ];

	for (i = 0; i < 64; i++)
	{
		temp1 = h + SI2(e) + F0(e, f, g) + k[ i ] + w[ i ];
		temp2 = SI1(a) + F1(a, b, c);

		h = g;
		g = f;
		f = e;
		e = d + temp1;
		d = c;
		c = b;
		b = a;
		a = temp1 + temp2;
	}

	Ctx->State[0] += a;
	Ctx->State[1] += b;
	Ctx->State[2] += c;
	Ctx->State[3] += d;
	Ctx->State[4] += e;
	Ctx->State[5] += f;
	Ctx->State[6] += g;
	Ctx->State[7] += h;
}


void Sha256Update(Sha256Ctx *Ctx, BYTE *data, size_t len)
{
	unsigned int  b_len = Ctx->Len & 63,
								r_len = (b_len ^ 63) + 1;

	Ctx->Len += (unsigned int)len;

	if ( len < r_len )
	{
		memcpy(Ctx->Buffer + b_len, data, len);
		return;
	}

	if ( r_len < 64 )
	{
		memcpy(Ctx->Buffer + b_len, data, r_len);
		len  -= r_len;
		data += r_len;
		Sha256ProcessBlock(Ctx, Ctx->Buffer);
	}

	for (; len >= 64; len -= 64, data += 64)
		Sha256ProcessBlock(Ctx, data);

	if ( len ) memcpy(Ctx->Buffer, data, len);
}


void Sha256Finish(Sha256Ctx *Ctx, BYTE *hash)
{
	unsigned int  i, b_len = Ctx->Len & 63;

	Ctx->Buffer[ b_len ] = 0x80;
	if ( b_len ^ 63 ) memset(Ctx->Buffer + b_len + 1, 0, b_len ^ 63);

	if ( b_len >= 56 )
	{
		Sha256ProcessBlock(Ctx, Ctx->Buffer);
		memset(Ctx->Buffer, 0, 56);
	}

	//PUT_UAA64BE(Ctx->Buffer, (unsigned long long)(Ctx->Len * 8), 7);
	((uint64_t*)Ctx->Buffer)[7] = std::byteswap((uint64_t)Ctx->Len << 3);
	Sha256ProcessBlock(Ctx, Ctx->Buffer);

	for (i = 0; i < 8; i++)
		//PUT_UAA32BE(hash, Ctx->State[i], i);
		((DWORD*)hash)[i] = std::byteswap(Ctx->State[i]);

}


void Sha256(BYTE *data, size_t len, BYTE *hash)
{
	Sha256Ctx Ctx;

	Sha256Init(&Ctx);
	Sha256Update(&Ctx, data, len);
	Sha256Finish(&Ctx, hash);
}