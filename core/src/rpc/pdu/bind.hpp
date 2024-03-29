// bind.hpp
// (C) Martin Alebachew, 2023

/*
This file defines the RPC Bind PDU struct.
*/

#pragma once
#pragma pack(push, 1)
#include "../primitives.hpp"
#include "../uuid.hpp"
#include "shared.hpp"
#include <cstdlib>
#include <cstring>
#include <vector>

typedef u_int16 p_context_id_t;

struct p_syntax_id_t {
  dce_uuid_t if_uuid;
  u_int32 if_version;
};

struct p_cont_elem_t {
  p_context_id_t p_cont_id;
  u_int8 n_transfer_syn; // Number of items
  u_int8 reserved;
  p_syntax_id_t abstract_syntax;
  p_syntax_id_t* transfer_syntaxes; // Heap-allocated array
};

struct p_cont_list_t {
  u_int8 n_context_elem; // Number of items
  u_int8 reserved;
  u_int16 reserved2;
  p_cont_elem_t* p_cont_elem; // Heap-allocated array
};

namespace RPC::PDU {
struct Bind {
  /* NOTE
  Modifying the properties below may break the casting algorithm.
  Adjust it accordingly.
  */

  u_int8 rpc_vers = 5;
  u_int8 rpc_vers_minor = 0;
  Type PTYPE = Type::bind;
  u_int8 pfc_flags = PFC_FIRST_FRAG | PFC_LAST_FRAG;
  byte packed_drep[4]; // NDR data rep format label
  u_int16 frag_length;
  u_int16 auth_length = 0;
  u_int32 call_id;

  u_int16 max_xmit_frag;  // Max transmit frag size, bytes
  u_int16 max_recv_frag;  // Max receive frag size, bytes
  u_int32 assoc_group_id; // Incarnation of client-server assoc group

  // Presentation context list, variable size
  p_cont_list_t p_context_elem;

  Bind(const std::vector<byte> &rawPDU);
  ~Bind();
};
} // namespace RPC::PDU

#pragma pack(pop)
