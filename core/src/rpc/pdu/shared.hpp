// shared.hpp
// (C) Martin Alebachew, 2023

/*
This file defines RPC PDU shared types.
*/

#pragma once
#include "../primitives.hpp"

// PFC_FLAGS
#define PFC_FIRST_FRAG      0x01
#define PFC_LAST_FRAG       0x02
#define PFC_PENDING_CANCEL  0x04
#define PFC_RESERVED_1      0x08
#define PFC_CONC_MPX        0x10
#define PFC_DID_NOT_EXECUTE 0x20
#define PFC_MAYBE           0x40
#define PFC_OBJECT_UUID     0x80

namespace RPC::PDU {
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
}; // namespace RPC::PDU
