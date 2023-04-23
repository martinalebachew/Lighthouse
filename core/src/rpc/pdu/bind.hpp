// bind.hpp
// (C) Martin Alebachew, 2023

/*
This file defines the RPC Bind PDU struct.
*/

#pragma once
#include "../presentation.hpp"
#include "../primitives.hpp"
#include "types.hpp"

namespace RPC::PDU {
struct Bind {
  u_int8 rpc_vers = 5;
  u_int8 rpc_vers_minor = 0;
  Type PTYPE = Type::bind;
  u_int8 pfc_flags;
  byte packed_drep[4]; // NDR data rep format label
  u_int16 frag_length;
  u_int16 auth_length = 0;
  u_int32 call_id;

  u_int16 max_xmit_frag;  // Max transmit frag size, bytes
  u_int16 max_recv_frag;  // Max receive frag size, bytes
  u_int32 assoc_group_id; // Incarnation of client-server assoc group

  // Presentation context list, variable size
  p_cont_list_t p_context_elem;
};
} // namespace RPC::PDU
