// response.hpp
// (C) Martin Alebachew, 2023

/*
This file defines the RPC Response PDU struct.
*/

#pragma once
#include "../primitives.hpp"
#include "../uuid.hpp"
#include "request.hpp"
#include "shared.hpp"
#include <cstdlib>
#include <cstring>
#include <vector>

namespace RPC::PDU {
struct Response {
  /* NOTE
  Modifying the properties below may break the casting algorithm.
  Adjust it accordingly.
  */

  u_int8 rpc_vers = 5;
  u_int8 rpc_vers_minor = 0;
  Type PTYPE = Type::response;
  u_int8 pfc_flags = PFC_FIRST_FRAG | PFC_LAST_FRAG;
  byte packed_drep[4]; // NDR data rep format label
  u_int16 frag_length;
  u_int16 auth_length = 0;
  u_int32 call_id;

  u_int32 alloc_hint = 0;
  p_context_id_t p_cont_id = 0;
  u_int8 cancel_count = 0;
  u_int8 reserved;

  std::vector<byte> stub;

  Response(Request &request, std::vector<byte> responseStub) {
    // TODO: Implement custom data representation that allows us to discard
    // endianess conversion when casting to a buffer. For now, we'll copy the
    // data representation of the client, as specified in the Bind PDU.
    memcpy(packed_drep, request.packed_drep, 4);

    call_id = request.call_id; // This value is set by the client
    stub = responseStub;
  }

  std::vector<byte> toBuffer() {
    frag_length = offsetof(Response, stub) + stub.size();
    alloc_hint = frag_length;

    std::vector<byte> buffer = std::vector<byte>(frag_length);
    memcpy(buffer.data(), this, offsetof(Response, stub));
    memcpy(buffer.data() + offsetof(Response, stub), stub.data(), stub.size());
    return buffer;
  }
} __attribute__((packed)); // Disabling compiler alignment in favor of RPC alignment
} // namespace RPC::PDU
