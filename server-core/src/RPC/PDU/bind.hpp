// bind.hpp
// (C) Martin Alebachew, 2023

/*
This file defines the RPC bind PDU wrapper struct.
*/

#pragma once
#include "../primitives.hpp"
#include "../uuid.hpp"
#include "shared.hpp"
#include <vector>

typedef u_int16 p_context_id_t;

struct p_syntax_id_t {
  dce_uuid_t if_uuid;
  u_int32 if_version;
} __attribute__((packed)); // Disabling compiler alignment in favor of RPC alignment.;

struct p_cont_elem_t {
  p_context_id_t p_cont_id;
  u_int8 n_transfer_syn;            /* number of items */
  u_int8 reserved;                  /* alignment pad, m.b.z. */
  p_syntax_id_t abstract_syntax;    /* transfer syntax list */
  p_syntax_id_t *transfer_syntaxes; // Heap-allocated array
} __attribute__((packed)); // Disabling compiler alignment in favor of RPC alignment.

struct p_cont_list_t {
  u_int8 n_context_elem;      /* number of items */
  u_int8 reserved;            /* alignment pad, m.b.z. */
  u_int16 reserved2;          /* alignment pad, m.b.z. */
  p_cont_elem_t *p_cont_elem; // Heap-allocated array
} __attribute__((packed)); // Disabling compiler alignment in favor of RPC alignment.

namespace RPC::PDU {
struct Bind {
  /* NOTE
     Modifying the properties below may break the casting algorithm.
     Adjust it accordingly.
  */

  /* common fields */
  u_int8 rpc_vers = 5;                               /* RPC version */
  u_int8 rpc_vers_minor = 0;                         /* minor version */
  Type PTYPE = Type::bind;                           /* bind PDU */
  u_int8 pfc_flags = PFC_FIRST_FRAG | PFC_LAST_FRAG; /* flags */
  byte packed_drep[4];     /* NDR data rep format label*/
  u_int16 frag_length;     /* total length of fragment */
  u_int16 auth_length = 0; /* length of auth_value */
  u_int32 call_id;         /* call identifier */
  /* end common fields */

  u_int16 max_xmit_frag;  /* max transmit frag size, bytes */
  u_int16 max_recv_frag;  /* max receive frag size, bytes */
  u_int32 assoc_group_id; /* incarnation of client-server assoc group */

  /* presentation context list */
  p_cont_list_t p_context_elem; /* variable size */

  Bind(const std::vector<byte> &rawPDU);
  ~Bind();
} __attribute__((packed)); // Disabling compiler alignment in favor of RPC alignment.
} // namespace RPC::PDU
