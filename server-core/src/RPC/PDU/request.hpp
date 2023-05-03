// request.hpp
// (C) Martin Alebachew, 2023

/*
This files defines the RPC request PDU wrapper struct.
*/

#pragma once
#include <cstring>
#include <cstdlib>
#include "../primitives.hpp"
#include "shared.hpp"
#include "../uuid.hpp"
#include "../../debug.hpp"

typedef u_int16 p_context_id_t;

namespace RPC::PDU {
struct Request {
    /* NOTE
       Modifying the properties below may break the casting algorithm.
       Adjust it accordingly.
    */

    /* common fields */
    u_int8 rpc_vers = 5; /* RPC version */
    u_int8 rpc_vers_minor = 0; /* minor version */
    Type PTYPE = Type::request ; /* request PDU */
    u_int8 pfc_flags = PFC_FIRST_FRAG | PFC_LAST_FRAG; /* flags */
    byte packed_drep[4]; /* NDR data rep format label*/
    u_int16 frag_length; /* total length of fragment */
    u_int16 auth_length = 0; /* length of auth_value */
    u_int32 call_id; /* call identifier */
    /* end common fields */

    /* needed on request, response, fault */
    u_int32 alloc_hint; /* allocation hint */
    p_context_id_t p_cont_id; /* pres context, i.e. data rep */
    u_int16 opnum; /* operation within the interface */

    /* optional field for request, only present if the PFC_OBJECT_UUID
    * field is non-zero */
    dce_uuid_t object_uuid; /* object UUID */

    /* 8-octet alignment might be present here */
    
    byte* stub_data;

    }
} __attribute__ ((packed)); // Disabling compiler alignment in favor of RPC alignment.
} // namespace RPC::PDU