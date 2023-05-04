// bind_ack.hpp
// (C) Martin Alebachew, 2023

/*
This files defines the RPC bindack PDU wrapper struct.
*/

#pragma once
#include "../primitives.hpp"
#include "bind.hpp"
#include "shared.hpp"
#include <cstdlib>
#include <cstring>
#include <limits>
#include <random>

struct port_any_t {
  u_int16 length;  // Includes null terminator
  char *port_spec; /* port heap-allocated string spec */

  port_any_t(u_int16 port) {
    // TODO: account for non-ascii representation in format label
    length = (int)log10(port) + 2; // account for null terminator
    port_spec = (char *)malloc(length);
    snprintf(port_spec, length, "%d", port);
  }
} __attribute__((
    packed)); // Disabling compiler alignment in favor of RPC alignment.;

enum struct p_provider_reason_t : u_int16 {
  reason_not_specified,
  abstract_syntax_not_supported,
  proposed_transfer_syntaxes_not_supported,
  local_limit_exceeded
};

enum struct p_cont_def_result_t : u_int16 {
  acceptance,
  user_rejection,
  provider_rejection
};

struct p_result_t {
  p_cont_def_result_t result;
  p_provider_reason_t reason; /* only relevant if result != acceptance */
  p_syntax_id_t
      transfer_syntax; /* tr syntax selected 0 if result not accepted */
} __attribute__((
    packed)); // Disabling compiler alignment in favor of RPC alignment.;

struct p_result_list_t {
  u_int8 n_results;      /* count */
  u_int8 reserved;       /* alignment pad, m.b.z. */
  u_int16 reserved2;     /* alignment pad, m.b.z. */
  p_result_t *p_results; // Heap-allocated array
} __attribute__((
    packed)); // Disabling compiler alignment in favor of RPC alignment.;

// TODO: account for different representation in format label
std::vector<byte> NDR_32_V2_TRANSFER_SYNTAX = {
    0x04, 0x5d, 0x88, 0x8a, 0xeb, 0x1c, 0xc9, 0x11, 0x9f, 0xe8,
    0x08, 0x00, 0x2b, 0x10, 0x48, 0x60, 0x02, 0x00, 0x00, 0x00};

namespace RPC::PDU {
struct BindAck {
  /* NOTE
     Modifying the properties below may break the casting algorithm.
     Adjust it accordingly.
  */

  /* common fields */
  u_int8 rpc_vers = 5;                               /* RPC version */
  u_int8 rpc_vers_minor = 0;                         /* minor version */
  Type PTYPE = Type::bind_ack;                       /* bind PDU */
  u_int8 pfc_flags = PFC_FIRST_FRAG | PFC_LAST_FRAG; /* flags */
  byte packed_drep[4];     /* NDR data rep format label */
  u_int16 frag_length;     /* total length of fragment */
  u_int16 auth_length = 0; /* length of auth_value */
  u_int32 call_id;         /* call identifier */
  /* end common fields */

  u_int16 max_xmit_frag;  /* max transmit frag size, bytes */
  u_int16 max_recv_frag;  /* max receive frag size, bytes */
  u_int32 assoc_group_id; /* incarnation of client-server assoc group */

  // TODO: get port from conversation
  port_any_t sec_addr; /* optional secondary address for back binding */

  /* 4-octet alignment pad might be present here */

  /* presentation context result list, including hints */
  p_result_list_t p_result_list; /* variable size */

  BindAck(Bind &bind, u_int16 port) : sec_addr(port) {
    // Adjust the multiplex flag according to the bind pdu
    if (bind.pfc_flags & PFC_CONC_MPX)
      pfc_flags |= PFC_CONC_MPX;

    // TODO: implement custom data representation that allows us to discard
    // endianess conversion when casting to a buffer For now, we'll copy the
    // data representation of the client, as specified in the bind PDU
    memcpy(packed_drep, bind.packed_drep, 4);

    call_id = bind.call_id; // This value is set by the client

    // Doesn't matter beacuse the server doesn't support fragmentation and
    // reassembly, yet this is the correct implementation of those fields:
    max_xmit_frag = bind.max_recv_frag; // Set the max transmit frag to the max
                                        // receive frag of the client
    max_recv_frag = bind.max_xmit_frag; // Set the max receive frag to the max
                                        // transmit frag of the client

    assoc_group_id = bind.assoc_group_id; // This value is set by the client
    if (!assoc_group_id) { // If the value is 0, the client is asking for a new
                           // association group
      // TODO: add proper implementation of random number generation
      // TODO: keep track of assoc_group_id in conversation / connection manager
      // of whole server
      srand((unsigned)time(NULL));
      assoc_group_id = (u_int32)rand();
    }

    // Allocate memory for the results list
    p_result_list.n_results = bind.p_context_elem.n_context_elem;
    p_result_list.p_results =
        (p_result_t *)malloc(p_result_list.n_results * sizeof(p_result_t));

    // TODO: implement proper support for multiple transfer syntaxes. for now,
    // assuming one transfer syntax per context element
    for (int i = 0; i < p_result_list.n_results; i++) {
      if (!memcmp(&bind.p_context_elem.p_cont_elem[i].transfer_syntaxes[0],
                  NDR_32_V2_TRANSFER_SYNTAX.data(),
                  NDR_32_V2_TRANSFER_SYNTAX.size())) {
        p_result_list.p_results[i].result = p_cont_def_result_t::acceptance;
        p_result_list.p_results[i].transfer_syntax =
            bind.p_context_elem.p_cont_elem[i].transfer_syntaxes[0];
      } else {
        p_result_list.p_results[i].result =
            p_cont_def_result_t::provider_rejection;
        p_result_list.p_results[i].reason =
            p_provider_reason_t::proposed_transfer_syntaxes_not_supported;
      }
    }
  }

  ~BindAck() { free(p_result_list.p_results); }

  std::vector<byte> toBuffer() {
    std::vector<byte> buffer = std::vector<byte>(
        offsetof(BindAck, sec_addr) +
        offsetof(port_any_t, port_spec)); // Allocate buffer with size of the
                                          // fixed-size properties
    unsigned int offset = 0; // Buffer offset of the next property to copy

    // Copy PDU fixed-size properties into the buffer
    memcpy(buffer.data() + offset, // Copy into the buffer
           this,                   // Copy from the beginning of this structure
           offsetof(BindAck, sec_addr) +
               offsetof(port_any_t, port_spec) // Copy all fixed-size properties
    );
    offset += offsetof(BindAck, sec_addr) + offsetof(port_any_t, port_spec);

    buffer.resize(buffer.size() +
                  sec_addr.length); // Resize the buffer to fit the port_spec
    memcpy(buffer.data() + offset,  // Copy into the buffer
           sec_addr.port_spec,      // Copy from the port array
           sec_addr.length          // Copy the whole port array
    );
    offset += sec_addr.length;

    // Port length and value 4-octet alignment
    unsigned int containerLength = sec_addr.length + sizeof(sec_addr.length);
    unsigned int alignmentSize = 4 - (containerLength % 4);
    buffer.resize(buffer.size() +
                  alignmentSize); // Resize the buffer to fit the alignment
    offset += alignmentSize;

    buffer.resize(
        buffer.size() +
        offsetof(p_result_list_t,
                 p_results));      // Resize the buffer to fit the fixed-size
                                   // properties of p_result_list_t
    memcpy(buffer.data() + offset, // Copy into the buffer
           &p_result_list,         // Copy from p_result_list structure
           offsetof(p_result_list_t,
                    p_results) // Copy p_result_list_t fixed-size properties
    );
    offset += offsetof(p_result_list_t, p_results);

    buffer.resize(
        buffer.size() +
        p_result_list.n_results *
            sizeof(p_result_t));    // Resize the buffer to fit the results list
    memcpy(buffer.data() + offset,  // Copy into the buffer
           p_result_list.p_results, // Copy from the results list
           p_result_list.n_results *
               sizeof(p_result_t) // Copy the whole results list
    );

    *(u_int16 *)(buffer.data() + offsetof(BindAck, frag_length)) =
        buffer.size(); // Adjust the frag_length field in the buffer

    return buffer;
  }
} __attribute__((
    packed)); // Disabling compiler alignment in favor of RPC alignment.
} // namespace RPC::PDU
