// pdus.hpp
// (C) Martin Alebachew, 2023

/*
This file contains PDU structure definitions and
underlaying data types that are directly relevant.
*/

#pragma once
#include "presentation.hpp"
#include "primitives.hpp"

enum struct PDU : u_int8 {
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

struct bind_pdu_t {
  u_int8 rpc_vers = 5;
  u_int8 rpc_vers_minor = 0;
  PDU_Types PTYPE = PDU_Types::bind;
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
