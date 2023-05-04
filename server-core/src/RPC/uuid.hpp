// uuid.hpp
// (C) Martin Alebachew, 2023

/*
This file contains an implementation for the
DCE variant of UUIDs, as defined in C706.
*/

#pragma once
#include "primitives.hpp"

typedef struct {
    UNSIGNED_LONG time_low;
    UNSIGNED_SHORT time_mid;
    UNSIGNED_SHORT time_hi_and_version;
    UNSIGNED_SMALL clock_seq_hi_and_reserved;
    UNSIGNED_SMALL clock_seq_low;
    char node[6];
} dce_uuid_t;