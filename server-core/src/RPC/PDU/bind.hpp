// bind.hpp
// (C) Martin Alebachew, 2023

/*
This files defines the RPC bind PDU wrapper class.
*/

#pragma once
#include "../primitives.hpp"
#include "../presentation.hpp"
#include "type.hpp"

namespace RPC::PDU {
// bind PDU
class Bind {
public:
    /* common fields */
    u_int8 rpc_vers = 5; /* 00:01 RPC version */
    u_int8 rpc_vers_minor = 0; /* 01:01 minor version */
    u_int8 PTYPE = (u_int8)Type::bind; /* 02:01 bind PDU */
    u_int8 pfc_flags; /* 03:01 flags */
    byte packed_drep[4]; /* 04:04 NDR data rep format label*/
    u_int16 frag_length; /* 08:02 total length of fragment */
    u_int16 auth_length = 0; /* 10:02 length of auth_value */
    u_int32 call_id; /* 12:04 call identifier */
    /* end common fields */

    u_int16 max_xmit_frag; /* 16:02 max transmit frag size, bytes */
    u_int16 max_recv_frag; /* 18:02 max receive frag size, bytes */
    u_int32 assoc_group_id; /* 20:04 incarnation of client-server assoc group */

    /* presentation context list */
    p_cont_list_t p_context_elem; /* variable size */

    // TODO: Add optional auth verifier here
};
} // namespace RPC::PDU
