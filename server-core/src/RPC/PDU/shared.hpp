// shared.hpp
// (C) Martin Alebachew, 2023

/*
This file defines RPC PDU shared types.
*/

#pragma once
#include "../primitives.hpp"

// PFC_FLAGS
#define PFC_FIRST_FRAG 0x01 /* First fragment */
#define PFC_LAST_FRAG 0x02 /* Last fragment */
#define PFC_PENDING_CANCEL 0x04 /* Cancel was pending at sender */
#define PFC_RESERVED_1 0x08
#define PFC_CONC_MPX 0x10 /* supports concurrent multiplexing of a single connection. */
#define PFC_DID_NOT_EXECUTE 0x20 /* only meaningful on ‘fault’ packet; if true, guaranteed call did not execute. */
#define PFC_MAYBE 0x40 /* ‘maybe’ call semantics requested */
#define PFC_OBJECT_UUID 0x80 /* if true, a non-nil object UUID was specified in the handle, and is present in the optional object field. If false, the object field is omitted. */

namespace RPC::PDU {
// PDU Types
enum struct Type : u_int8 {
    request,
    ping,
    response,
    fault,
    working,
    nocall,
    reject,
    ack,
    cl_cancel,
    fack,
    cancel_ack,
    bind,
    bind_ack,
    bind_nak,
    alter_context,
    alter_context_resp,
    shutdown = 17, // Skipping 16 as defined in C706
    co_cancel,
    orphaned
};
};