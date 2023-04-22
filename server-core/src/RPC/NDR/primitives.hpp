// primitives.hpp
// (C) Martin Alebachew, 2023

#include <cstdint>

/* See C706 §14.2 NDR Primitive Types */

typedef bool BOOL;
typedef char ASCII_CHAR;
typedef char EBCDIC_CHAR;

typedef int8_t SMALL;
typedef int16_t SHORT;
typedef int32_t LONG;
typedef int64_t HYPER;

typedef int8_t USMALL;
typedef int16_t USHORT;
typedef int32_t ULONG;
typedef int64_t UHYPER;

typedef SHORT ENUM;

typedef int32_t IEEE_SINGLE;
typedef int64_t IEEE_DOUBLE;

typedef int32_t VAX_F;
typedef int64_t VAX_G;

typedef int32_t CRAY_SINGLE;
typedef int64_t CRAY_DOUBLE;

typedef int32_t IBM_SHORT;
typedef int64_t IBM_LONG;

typedef char RAW;