// bind_ack.cpp
// (C) Martin Alebachew, 2023

/*
This files defines the RPC bindack PDU wrapper struct.
*/

#include "bind_ack.hpp"

namespace RPC::PDU {
BindAck::BindAck(Bind &bind, u_int16 port) : sec_addr(port) {
  // Adjust the multiplex flag according to the bind pdu
  if (bind.pfc_flags & PFC_CONC_MPX) pfc_flags |= PFC_CONC_MPX;

  // TODO: implement custom data representation that allows us to discard
  // endianess conversion when casting to a buffer For now, we'll copy the
  // data representation of the client, as specified in the bind PDU
  memcpy(packed_drep, bind.packed_drep, 4);

  call_id = bind.call_id; // This value is set by the client

  // Doesn't matter beacuse the server doesn't support fragmentation and
  // reassembly, yet this is the correct implementation of those fields:
  max_xmit_frag = bind.max_recv_frag; // Set the max transmit frag to the max receive frag of the client
  max_recv_frag = bind.max_xmit_frag; // Set the max receive frag to the max transmit frag of the client

  assoc_group_id = bind.assoc_group_id; // This value is set by the client

  // If the value is 0, the client is asking for a new association group
  if (!assoc_group_id) {
    // TODO: add proper implementation of random number generation
    // TODO: keep track of assoc_group_id in conversation / connection manager of whole server
    srand((unsigned)time(NULL));
    assoc_group_id = (u_int32)rand();
  }

  // Allocate memory for the results list
  p_result_list.n_results = bind.p_context_elem.n_context_elem;
  p_result_list.p_results = (p_result_t *)malloc(p_result_list.n_results * sizeof(p_result_t));

  // TODO: implement proper support for multiple transfer syntaxes. for now,
  // Assuming one transfer syntax per context element

  // Accept NDR32 transfer syntax and reject all others, including bind time feature negotiation that requires alter_context and alter_context_resp PDUs
  for (int i = 0; i < p_result_list.n_results; i++) {
    if (!memcmp(&bind.p_context_elem.p_cont_elem[i].transfer_syntaxes[0], NDR_32_V2_TRANSFER_SYNTAX.data(), NDR_32_V2_TRANSFER_SYNTAX.size())) {
      p_result_list.p_results[i].result = p_cont_def_result_t::acceptance;
      p_result_list.p_results[i].transfer_syntax = bind.p_context_elem.p_cont_elem[i].transfer_syntaxes[0];
    } else {
      p_result_list.p_results[i].result = p_cont_def_result_t::provider_rejection;
      p_result_list.p_results[i].reason = p_provider_reason_t::proposed_transfer_syntaxes_not_supported;
    }
  }
}

BindAck::~BindAck() {
  free(p_result_list.p_results);
}

std::vector<byte> BindAck::toBuffer() {
  // Allocate buffer with size of the fixed-size properties
  std::vector<byte> buffer = std::vector<byte>(offsetof(BindAck, sec_addr) + offsetof(port_any_t, port_spec));

  // Copy PDU fixed-size properties into the buffer
  memcpy(buffer.data(), // Copy into the buffer
          this, // Copy from the beginning of this structure
          offsetof(BindAck, sec_addr) + offsetof(port_any_t, port_spec) // Copy all fixed-size properties
  );

  // Buffer offset of the next property to copy
  unsigned int offset = offsetof(BindAck, sec_addr) + offsetof(port_any_t, port_spec);

  // Resize the buffer to fit the port_spec
  buffer.resize(buffer.size() + sec_addr.length);
  memcpy(buffer.data() + offset, // Copy into the buffer
          sec_addr.port_spec, // Copy from the port array
          sec_addr.length // Copy the whole port array
  );

  offset += sec_addr.length;

  // Port length and value 4-octet alignment
  unsigned int containerLength = sec_addr.length + sizeof(sec_addr.length);
  unsigned int alignmentSize = 4 - (containerLength % 4);

  // Resize the buffer to fit the alignment
  buffer.resize(buffer.size() + alignmentSize);
  offset += alignmentSize;

  // Resize the buffer to fit the fixed-size properties of p_result_list_t
  buffer.resize(buffer.size() + offsetof(p_result_list_t, p_results));
  memcpy(buffer.data() + offset, // Copy into the buffer
          &p_result_list, // Copy from p_result_list structure
          offsetof(p_result_list_t, p_results) // Copy p_result_list_t fixed-size properties
  );

  offset += offsetof(p_result_list_t, p_results);

  // Resize the buffer to fit the results list
  buffer.resize(buffer.size() + p_result_list.n_results * sizeof(p_result_t));
  memcpy(buffer.data() + offset, // Copy into the buffer
          p_result_list.p_results, // Copy from the results list
          p_result_list.n_results * sizeof(p_result_t) // Copy the whole results list
  );

  // Adjust the frag_length field in the buffer
  *(u_int16 *)(buffer.data() + offsetof(BindAck, frag_length)) = buffer.size();

  return buffer;
}
} // namespace RPC::PDU
