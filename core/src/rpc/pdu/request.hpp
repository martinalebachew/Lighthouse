// request.hpp
// (C) Martin Alebachew, 2023

/*
This file defines the RPC Request PDU struct.
*/

#pragma once
#include "../primitives.hpp"
#include "../uuid.hpp"
#include "shared.hpp"
#include <cstdlib>
#include <cstring>

typedef u_int16 p_context_id_t;

namespace RPC::PDU {
struct Request {
  /* NOTE
  Modifying the properties below may break the casting algorithm.
  Adjust it accordingly.
  */

  u_int8 rpc_vers = 5;
  u_int8 rpc_vers_minor = 0;
  Type PTYPE = Type::request;
  u_int8 pfc_flags = PFC_FIRST_FRAG | PFC_LAST_FRAG;
  byte packed_drep[4]; // NDR data rep format label
  u_int16 frag_length;
  u_int16 auth_length = 0;
  u_int32 call_id;

  u_int32 alloc_hint;
  p_context_id_t p_cont_id;
  u_int16 opnum; // Operation within the interface

  // Optional, unsupported value. Requires matching flag turned on
  dce_uuid_t object_uuid;

  byte* stub_data;

  Request(const std::vector<byte> &rawPDU) {
    // Copy PDU fixed-size properties
    memcpy(this, rawPDU.data(), offsetof(Request, object_uuid));

    // Calculate stub_data length
    unsigned int stub_data_length = rawPDU.size() - offsetof(Request, object_uuid);

    // Set object_uuid property
    if (pfc_flags & PFC_OBJECT_UUID) {
      // Copy object_uuid from the raw PDU
      memcpy(
        &object_uuid, rawPDU.data() + offsetof(Request, object_uuid), sizeof(object_uuid)
      );

      // Subtract object_uuid length, as it is present in the raw PDU
      stub_data_length -= sizeof(object_uuid);
    }

    // Allocate and copy stub_data from the raw PDU
    stub_data = (byte*)malloc(stub_data_length);
    memcpy(stub_data, rawPDU.data() + rawPDU.size() - stub_data_length, stub_data_length);
  }

  ~Request() {
    free(stub_data);
  }
} __attribute__((packed)); // Disabling compiler alignment in favor of RPC alignment
} // namespace RPC::PDU
