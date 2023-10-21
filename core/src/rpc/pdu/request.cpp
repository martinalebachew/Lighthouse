// request.cpp
// (C) Martin Alebachew, 2023

/*
This file implements the RPC Request PDU struct.
*/

#include "request.hpp"

namespace RPC::PDU {
Request::Request(const std::vector<byte> &rawPDU) {
  // Copy PDU fixed-size properties
  memcpy(this, rawPDU.data(), offsetof(Request, object_uuid));

  // Calculate stub length
  unsigned int stubLength = rawPDU.size() - offsetof(Request, object_uuid);

  // Set object_uuid property
  if (pfc_flags & PFC_OBJECT_UUID) {
    // Copy object_uuid from the raw PDU
    memcpy(&object_uuid, rawPDU.data() + offsetof(Request, object_uuid), sizeof(object_uuid));

    // Subtract object_uuid length, as it is present in the raw PDU
    stubLength -= sizeof(object_uuid);
  }

  // Copy stub from the raw PDU
  stub.resize(stubLength);
  memcpy(stub.data(), rawPDU.data() + rawPDU.size() - stubLength, stubLength);
}
} // namespace RPC::PDU
