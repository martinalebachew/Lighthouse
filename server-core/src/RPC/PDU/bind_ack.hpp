// bind_ack.hpp
// (C) Martin Alebachew, 2023

/*
This files defines the RPC bindack PDU wrapper struct.
*/

#pragma once
#include "../primitives.hpp"
#include "bind.hpp"
#include "shared.hpp"
#include <cstdlib>
#include <cstring>
#include <limits>
#include <random>

struct port_any_t {
  u_int16 length;  // Includes null terminator
  char *port_spec; /* port heap-allocated string spec */

  port_any_t(u_int16 port) {
    // TODO: account for non-ascii representation in format label
    length = (int)log10(port) + 2; // account for null terminator
    port_spec = (char *)malloc(length);
    snprintf(port_spec, length, "%d", port);
  }
} __attribute__((
    packed)); // Disabling compiler alignment in favor of RPC alignment.;

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
  p_provider_reason_t reason; /* only relevant if result != acceptance */
  p_syntax_id_t
      transfer_syntax; /* tr syntax selected 0 if result not accepted */
} __attribute__((
    packed)); // Disabling compiler alignment in favor of RPC alignment.;

struct p_result_list_t {
  u_int8 n_results;      /* count */
  u_int8 reserved = 0;   /* alignment pad, m.b.z. */
  u_int16 reserved2 = 0; /* alignment pad, m.b.z. */
  p_result_t *p_results; // Heap-allocated array
} __attribute__((
    packed)); // Disabling compiler alignment in favor of RPC alignment.;

// TODO: account for different representation in format label
const std::vector<byte> NDR_32_V2_TRANSFER_SYNTAX = {
    0x04, 0x5d, 0x88, 0x8a, 0xeb, 0x1c, 0xc9, 0x11, 0x9f, 0xe8,
    0x08, 0x00, 0x2b, 0x10, 0x48, 0x60, 0x02, 0x00, 0x00, 0x00};

namespace RPC::PDU {
struct BindAck {
  /* NOTE
     Modifying the properties below may break the casting algorithm.
     Adjust it accordingly.
  */

  /* common fields */
  u_int8 rpc_vers = 5;                               /* RPC version */
  u_int8 rpc_vers_minor = 0;                         /* minor version */
  Type PTYPE = Type::bind_ack;                       /* bind PDU */
  u_int8 pfc_flags = PFC_FIRST_FRAG | PFC_LAST_FRAG; /* flags */
  byte packed_drep[4];     /* NDR data rep format label */
  u_int16 frag_length;     /* total length of fragment */
  u_int16 auth_length = 0; /* length of auth_value */
  u_int32 call_id;         /* call identifier */
  /* end common fields */

  u_int16 max_xmit_frag;  /* max transmit frag size, bytes */
  u_int16 max_recv_frag;  /* max receive frag size, bytes */
  u_int32 assoc_group_id; /* incarnation of client-server assoc group */

  // TODO: get port from conversation
  port_any_t sec_addr; /* optional secondary address for back binding */

  /* 4-octet alignment pad might be present here */

  /* presentation context result list, including hints */
  p_result_list_t p_result_list; /* variable size */

  BindAck(Bind &bind, u_int16 port);
  ~BindAck();
  std::vector<byte> toBuffer();
} __attribute__((packed)); // Disabling compiler alignment in favor of RPC alignment.
} // namespace RPC::PDU
