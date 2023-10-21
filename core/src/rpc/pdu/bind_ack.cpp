// bind_ack.cpp
// (C) Martin Alebachew, 2023

/*
This file implements the RPC BindAck PDU struct.
*/

#include "bind_ack.hpp"

// TODO: Account for different representations in format label
const std::vector<byte> NDR_32_V2_TRANSFER_SYNTAX = {
  0x04, 0x5d, 0x88, 0x8a, 0xeb, 0x1c, 0xc9, 0x11, 0x9f, 0xe8,
  0x08, 0x00, 0x2b, 0x10, 0x48, 0x60, 0x02, 0x00, 0x00, 0x00
};

namespace RPC::PDU {
BindAck::BindAck(Bind &bind, u_int16 port) : sec_addr(port) {
  // TODO: Implement custom data representation that allows us to discard
  // endianess conversion when casting to a buffer or now, we'll copy
  // the data representation of the client, as specified in the Bind PDU
  memcpy(packed_drep, bind.packed_drep, 4);

  // Adjust the multiplex flag according to the Bind PDU
  if (bind.pfc_flags & PFC_CONC_MPX) pfc_flags |= PFC_CONC_MPX;

  call_id = bind.call_id; // This value is set by the client

  // Doesn't matter beacuse the server doesn't support fragmentation and reassembly,
  // yet this is the correct implementation of those fields:

  // Set the max transmit frag to the max receive frag of the client
  max_xmit_frag = bind.max_recv_frag;

  // Set the max receive frag to the max transmit frag of the client
  max_recv_frag = bind.max_xmit_frag;

  // This value is set by the client
  assoc_group_id = bind.assoc_group_id;

  // If the value is 0, the client is asking for a new association group
  if (!assoc_group_id) {
    // TODO: Add proper implementation of random number generation
    // TODO: Keep track of assoc_group_id in conversation / connection manager of whole server
    srand((unsigned)time(NULL));
    assoc_group_id = (u_int32)rand();
  }

  // Allocate memory for the results list
  p_result_list.n_results = bind.p_context_elem.n_context_elem;
  p_result_list.p_results = (p_result_t*)malloc(p_result_list.n_results * sizeof(p_result_t));

  // TODO: Implement proper support for multiple transfer syntaxes
  // For now, assuming one transfer syntax per context element

  // Accept NDR32 transfer syntax and reject all others, including bind time
  // feature negotiation that requires alter_context and alter_context_resp PDUs
  for (int i = 0; i < p_result_list.n_results; i++) {
    if (!memcmp(
          &bind.p_context_elem.p_cont_elem[i].transfer_syntaxes[0],
          NDR_32_V2_TRANSFER_SYNTAX.data(), NDR_32_V2_TRANSFER_SYNTAX.size()
        )) {
      p_result_list.p_results[i].result = p_cont_def_result_t::acceptance;
      p_result_list.p_results[i].transfer_syntax =
        bind.p_context_elem.p_cont_elem[i].transfer_syntaxes[0];
    } else {
      p_result_list.p_results[i].result = p_cont_def_result_t::provider_rejection;
      p_result_list.p_results[i].reason =
        p_provider_reason_t::proposed_transfer_syntaxes_not_supported;
    }
  }
}

BindAck::~BindAck() {
  free(p_result_list.p_results);
}

std::vector<byte> BindAck::toBuffer() {
  // Allocate buffer with size of the fixed-size properties
  std::vector<byte> buffer =
    std::vector<byte>(offsetof(BindAck, sec_addr) + offsetof(port_any_t, port_spec));

  // Copy PDU fixed-size properties into the buffer
  memcpy(buffer.data(), this, offsetof(BindAck, sec_addr) + offsetof(port_any_t, port_spec));

  // Buffer offset of the next property to copy
  unsigned int offset = offsetof(BindAck, sec_addr) + offsetof(port_any_t, port_spec);

  // Resize the buffer to fit the port_spec
  buffer.resize(buffer.size() + sec_addr.length);
  memcpy(buffer.data() + offset, sec_addr.port_spec, sec_addr.length);
  offset += sec_addr.length;

  // Port length and value 4-octet alignment
  unsigned int containerLength = sec_addr.length + sizeof(sec_addr.length);
  unsigned int alignmentSize = 4 - (containerLength % 4);

  // Resize the buffer to fit the alignment
  buffer.resize(buffer.size() + alignmentSize);
  offset += alignmentSize;

  // Resize the buffer to fit the fixed-size properties of p_result_list_t
  buffer.resize(buffer.size() + offsetof(p_result_list_t, p_results));
  memcpy(buffer.data() + offset, &p_result_list, offsetof(p_result_list_t, p_results));
  offset += offsetof(p_result_list_t, p_results);

  // Resize the buffer to fit the results list
  buffer.resize(buffer.size() + p_result_list.n_results * sizeof(p_result_t));
  memcpy(
    buffer.data() + offset, p_result_list.p_results,
    p_result_list.n_results * sizeof(p_result_t)
  );

  // Adjust the frag_length field in the buffer
  *(u_int16*)(buffer.data() + offsetof(BindAck, frag_length)) = buffer.size();

  return buffer;
}
} // namespace RPC::PDU
