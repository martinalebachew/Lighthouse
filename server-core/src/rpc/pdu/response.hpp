// response.hpp
// (C) Martin Alebachew, 2023

/*
This files defines the RPC response PDU wrapper struct.
*/

#pragma once
#include "request.hpp"
#include "shared.hpp"
#include "../primitives.hpp"
#include "../uuid.hpp"
#include <vector>

namespace RPC::PDU {
struct Response {
  /* NOTE
     Modifying the properties below may break the casting algorithm.
     Adjust it accordingly.
  */

  /* common fields */
  u_int8 rpc_vers = 5;                               /* RPC version */
  u_int8 rpc_vers_minor = 0;                         /* minor version */
  Type PTYPE = Type::response;                       /* bind PDU */
  u_int8 pfc_flags = PFC_FIRST_FRAG | PFC_LAST_FRAG; /* flags */
  byte packed_drep[4];     /* NDR data rep format label */
  u_int16 frag_length;     /* total length of fragment */
  u_int16 auth_length = 0; /* length of auth_value */
  u_int32 call_id;         /* call identifier */
  /* end common fields */

  u_int32 alloc_hint = 0; /* allocation hint */
  p_context_id_t p_cont_id = 0; /* pres context, i.e. data rep */
  u_int8 cancel_count = 0; /* cancel count */
  u_int8 reserved; /* reserved, m.b.z. */

  std::vector<byte> stub;

  Response(Request &request, std::vector<byte> responseStub);
  std::vector<byte> toBuffer();
} __attribute__((packed)); // Disabling compiler alignment in favor of RPC alignment.
} // namespace RPC::PDU
