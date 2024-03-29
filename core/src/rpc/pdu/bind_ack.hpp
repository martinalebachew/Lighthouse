// bind_ack.hpp
// (C) Martin Alebachew, 2023

/*
This file defines the RPC BindAck PDU struct.
*/

#pragma once
#pragma pack(push, 1)
#include "../primitives.hpp"
#include "bind.hpp"
#include "shared.hpp"
#include <cstdlib>
#include <cstring>
#include <limits>
#include <random>

struct port_any_t {
  u_int16 length;  // Includes null terminator
  char* port_spec; // Port heap-allocated string spec

  port_any_t(u_int16 port) {
    // TODO: Account for non-ascii representation in format label
    length = (int)log10(port) + 2; // Account for null terminator
    port_spec = (char*)malloc(length);
    snprintf(port_spec, length, "%d", port);
  }
};

enum struct p_provider_reason_t : u_int16 {
  reason_not_specified,
  abstract_syntax_not_supported,
  proposed_transfer_syntaxes_not_supported,
  local_limit_exceeded
};

enum struct p_cont_def_result_t : u_int16 {
  acceptance,
  user_rejection,
  provider_rejection
};

struct p_result_t {
  p_cont_def_result_t result;
  p_provider_reason_t reason;
  p_syntax_id_t transfer_syntax;
};

struct p_result_list_t {
  u_int8 n_results; // Number of items
  u_int8 reserved = 0;
  u_int16 reserved2 = 0;
  p_result_t* p_results; // Heap-allocated array
};

namespace RPC::PDU {
struct BindAck {
  /* NOTE
  Modifying the properties below may break the casting algorithm.
  Adjust it accordingly.
  */

  u_int8 rpc_vers = 5;
  u_int8 rpc_vers_minor = 0;
  Type PTYPE = Type::bind_ack;
  u_int8 pfc_flags = PFC_FIRST_FRAG | PFC_LAST_FRAG;
  byte packed_drep[4]; // NDR data rep format label
  u_int16 frag_length;
  u_int16 auth_length = 0;
  u_int32 call_id;

  u_int16 max_xmit_frag;  // Max transmit frag size, bytes
  u_int16 max_recv_frag;  // Max receive frag size, bytes
  u_int32 assoc_group_id; // Incarnation of client-server assoc group

  port_any_t sec_addr; // Optional secondary address for back binding

  // 4-octet alignment pad might be present here

  // Presentation context result list, including hints, variable size
  p_result_list_t p_result_list;

  BindAck(Bind &bind, u_int16 port);
  ~BindAck();
  std::vector<byte> toBuffer();
};
} // namespace RPC::PDU

#pragma pack(pop)
