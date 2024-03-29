// response.cpp
// (C) Martin Alebachew, 2023

/*
This file implements the RPC Response PDU struct.
*/

#include "response.hpp"

namespace RPC::PDU {
Response::Response(Request &request, std::vector<byte> responseStub) {
  // TODO: Implement custom data representation that allows us to discard
  // endianess conversion when casting to a buffer. For now, we'll copy the
  // data representation of the client, as specified in the Bind PDU.
  memcpy(packed_drep, request.packed_drep, 4);

  call_id = request.call_id; // This value is set by the client
  stub = responseStub;
}

std::vector<byte> Response::toBuffer() {
  frag_length = offsetof(Response, stub) + stub.size();
  alloc_hint = stub.size();

  std::vector<byte> buffer = std::vector<byte>(frag_length);
  memcpy(buffer.data(), this, offsetof(Response, stub));
  memcpy(buffer.data() + offsetof(Response, stub), stub.data(), stub.size());
  return buffer;
}
} // namespace RPC::PDU
