// bind.hpp
// (C) Martin Alebachew, 2023

/*
This file defines the RPC Bind PDU struct.
*/

#pragma once
#include "../primitives.hpp"
#include "../uuid.hpp"
#include "shared.hpp"
#include <cstdlib>
#include <cstring>
#include <vector>

typedef u_int16 p_context_id_t;

struct p_syntax_id_t {
  dce_uuid_t if_uuid;
  u_int32 if_version;
} __attribute__((packed)); // Disabling compiler alignment in favor of RPC alignment

struct p_cont_elem_t {
  p_context_id_t p_cont_id;
  u_int8 n_transfer_syn; // Number of items
  u_int8 reserved;
  p_syntax_id_t abstract_syntax;
  p_syntax_id_t* transfer_syntaxes; // Heap-allocated array
} __attribute__((packed));          // Disabling compiler alignment in favor of RPC alignment

struct p_cont_list_t {
  u_int8 n_context_elem; // Number of items
  u_int8 reserved;
  u_int16 reserved2;
  p_cont_elem_t* p_cont_elem; // Heap-allocated array
} __attribute__((packed));    // Disabling compiler alignment in favor of RPC alignment

namespace RPC::PDU {
struct Bind {
  /* NOTE
  Modifying the properties below may break the casting algorithm.
  Adjust it accordingly.
  */

  u_int8 rpc_vers = 5;
  u_int8 rpc_vers_minor = 0;
  Type PTYPE = Type::bind;
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

  Bind(const std::vector<byte> &rawPDU) {
    // Copy PDU fixed-size properties, including those nested in p_cont_list_t type
    memcpy(
      this, rawPDU.data(),
      offsetof(Bind, p_context_elem) + offsetof(p_cont_list_t, p_cont_elem)
    );

    // Allocate array of p_cont_list_t->p_cont_elem_t on the heap
    p_context_elem.p_cont_elem =
      (p_cont_elem_t*)malloc(p_context_elem.n_context_elem * sizeof(p_cont_elem_t));

    // Iterate through p_cont_list_t->p_cont_elem_t elements
    p_cont_elem_t* CurrContElemPtr =
      (p_cont_elem_t*)(rawPDU.data() + offsetof(Bind, p_context_elem) +
                       offsetof(p_cont_list_t, p_cont_elem));

    for (int i = 0; i < p_context_elem.n_context_elem; i++) {
      // Copy all fixed-size properties from the raw PDU into the heap-allocated array
      memcpy(
        (void*)(&p_context_elem.p_cont_elem[i]), CurrContElemPtr,
        offsetof(p_cont_elem_t, transfer_syntaxes)
      );

      // Allocate array of p_cont_list_t->p_cont_elem_t->p_syntax_id_t on the heap
      p_context_elem.p_cont_elem[i].transfer_syntaxes = (p_syntax_id_t*)
        malloc(p_context_elem.p_cont_elem[i].n_transfer_syn * sizeof(p_syntax_id_t));

      // Iterate through p_cont_list_t->p_cont_elem_t->p_syntax_id_t elements
      // Pointer to the transfer_syntaxes data
      p_syntax_id_t* CurrSyntaxIdPtr =
        (p_syntax_id_t*)((byte*)CurrContElemPtr + offsetof(p_cont_elem_t, transfer_syntaxes));

      for (int j = 0; j < p_context_elem.p_cont_elem[i].n_transfer_syn; j++) {
        // Copy all properties from the raw PDU into the heap-allocated array
        memcpy(
          (void*)(&p_context_elem.p_cont_elem[i].transfer_syntaxes[j]),
          CurrSyntaxIdPtr, sizeof(p_syntax_id_t)
        );

        CurrSyntaxIdPtr += 1; // Advance the pointer to the next p_syntax_id_t
      }

      // Set the next p_cont_list_t->p_cont_elem_t element
      CurrContElemPtr = (p_cont_elem_t*)CurrSyntaxIdPtr;
    }
  }

  ~Bind() {
    for (int i = 0; i < p_context_elem.n_context_elem; i++)
      free(p_context_elem.p_cont_elem[i].transfer_syntaxes);
    free(p_context_elem.p_cont_elem);
  }
} __attribute__((packed)); // Disabling compiler alignment in favor of RPC alignment
} // namespace RPC::PDU
