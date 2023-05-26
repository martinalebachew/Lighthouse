// primitives.hpp
// (C) Martin Alebachew, 2023

/*
This file contains definitions for primitive types used by
the RPC protocol. This includes both types defined under
    C706 §14.2 NDR Primitive Types,
and types defined under
    C706 §12.6.3.1 Declarations.
*/

#pragma once
#include <cstdint>

// C706 §14.2 NDR Primitive Types
typedef bool BOOL;
typedef char ASCII_CHAR;
typedef char EBCDIC_CHAR;

typedef int8_t SMALL;
typedef int16_t SHORT;
typedef int32_t LONG;
typedef int64_t HYPER;

typedef uint8_t UNSIGNED_SMALL;
typedef uint16_t UNSIGNED_SHORT;
typedef uint32_t UNSIGNED_LONG;
typedef uint64_t UNSIGNED_HYPER;

typedef SHORT ENUM;

typedef int32_t IEEE_SINGLE;
typedef int64_t IEEE_DOUBLE;

typedef int32_t VAX_F;
typedef int64_t VAX_G;

typedef int32_t CRAY_SINGLE;
typedef int64_t CRAY_DOUBLE;

typedef int32_t IBM_SHORT;
typedef int64_t IBM_LONG;

// C706 §12.6.3.1 Declarations
typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t u_int8;
typedef uint16_t u_int16;
typedef uint32_t u_int32;
typedef uint64_t u_int64;

typedef unsigned char byte;
