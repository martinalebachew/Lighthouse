// bind.cpp
// (C) Martin Alebachew, 2023

/*
This file defines the RPC bind PDU wrapper struct.
*/

#include "bind.hpp"

namespace RPC::PDU {
Bind::Bind(const std::vector<byte> &rawPDU) {
  // Copy PDU fixed-size properties, including those nested in p_cont_list_t type.
  memcpy(this, // Copy into the beginning of this structure
          rawPDU.data(), // Copy from the beginning of the raw PDU
          offsetof(Bind, p_context_elem) + offsetof(p_cont_list_t, p_cont_elem)
          // Copy all fixed-size properties, including those nested in p_cont_list_t type.
  );

  // Allocate array of p_cont_list_t->p_cont_elem_t on the heap
  p_context_elem.p_cont_elem = (p_cont_elem_t *)malloc(p_context_elem.n_context_elem * sizeof(p_cont_elem_t));

  // Iterate through p_cont_list_t->p_cont_elem_t elements
  p_cont_elem_t *CurrContElemPtr = (p_cont_elem_t *)(rawPDU.data() + offsetof(Bind, p_context_elem) + offsetof(p_cont_list_t, p_cont_elem));

  for (int i = 0; i < p_context_elem.n_context_elem; i++) {
    memcpy((void *)(&p_context_elem.p_cont_elem[i]), // Copy into the heap-allocated array
            CurrContElemPtr, // Copy from the calculated offset in the raw PDU
            offsetof(p_cont_elem_t, transfer_syntaxes) // Copy all fixed-size properties
    );

    // Allocate array of p_cont_list_t->p_cont_elem_t->p_syntax_id_t on the heap
    p_context_elem.p_cont_elem[i].transfer_syntaxes = (p_syntax_id_t *)malloc(p_context_elem.p_cont_elem[i].n_transfer_syn * sizeof(p_syntax_id_t));

    // Iterate through p_cont_list_t->p_cont_elem_t->p_syntax_id_t elements
    // Pointer to the transfer_syntaxes data
    p_syntax_id_t *CurrSyntaxIdPtr = (p_syntax_id_t *)((byte *)CurrContElemPtr + offsetof(p_cont_elem_t, transfer_syntaxes));

    for (int j = 0; j < p_context_elem.p_cont_elem[i].n_transfer_syn; j++) {
      memcpy((void *)(&p_context_elem.p_cont_elem[i].transfer_syntaxes[j]), // Copy into the heap-allocated array
          CurrSyntaxIdPtr, // Copy from the calculated offset in the raw PDU
          sizeof(p_syntax_id_t) // Copy all properties
      );

      CurrSyntaxIdPtr += 1; // Advance the pointer to the next p_syntax_id_t
    }

    // Set the next p_cont_list_t->p_cont_elem_t element
    CurrContElemPtr = (p_cont_elem_t *)CurrSyntaxIdPtr;
  }
}

Bind::~Bind() {
  for (int i = 0; i < p_context_elem.n_context_elem; i++)
    free(p_context_elem.p_cont_elem[i].transfer_syntaxes);
  free(p_context_elem.p_cont_elem);
}
} // namespace RPC::PDU
