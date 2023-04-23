// presentation.hpp
// (C) Martin Alebachew, 2023

/*
This file contains type and structure definitions
for presentation context.
*/

#pragma once
#include "primitives.hpp"
#include "uuid.hpp"

typedef u_int16 p_context_id_t;

typedef struct {
    dce_uuid_t if_uuid;
    u_int32 if_version;
} p_syntax_id_t;

typedef struct {
    p_context_id_t p_cont_id;
    u_int8 n_transfer_syn; /* number of items */
    u_int8 reserved; /* alignment pad, m.b.z. */
    p_syntax_id_t abstract_syntax; /* transfer syntax list */
    p_syntax_id_t transfer_syntaxes[];
} p_cont_elem_t;

typedef struct {
    u_int8 n_context_elem; /* number of items */
    u_int8 reserved; /* alignment pad, m.b.z. */
    u_int16 reserved2; /* alignment pad, m.b.z. */
    p_cont_elem_t p_cont_elem[];
} p_cont_list_t;