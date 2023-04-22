// pdus.hpp
// (C) Martin Alebachew, 2023

#pragma once
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
