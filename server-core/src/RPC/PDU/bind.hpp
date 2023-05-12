// bind.hpp
// (C) Martin Alebachew, 2023

/*
This file defines the RPC bind PDU wrapper struct.
*/

#pragma once
#include "../primitives.hpp"
#include "../uuid.hpp"
#include "shared.hpp"
#include <cstdlib>
#include <cstring>

typedef u_int16 p_context_id_t;

struct p_syntax_id_t {
    dce_uuid_t if_uuid;
    u_int32 if_version;
} __attribute__((
                    packed)); // Disabling compiler alignment in favor of RPC alignment.;

struct p_cont_elem_t {
    p_context_id_t p_cont_id;
    u_int8 n_transfer_syn;            /* number of items */
    u_int8 reserved;                  /* alignment pad, m.b.z. */
    p_syntax_id_t abstract_syntax;    /* transfer syntax list */
    p_syntax_id_t *transfer_syntaxes; // Heap-allocated array
} __attribute__((
                    packed)); // Disabling compiler alignment in favor of RPC alignment.

struct p_cont_list_t {
    u_int8 n_context_elem;      /* number of items */
    u_int8 reserved;            /* alignment pad, m.b.z. */
    u_int16 reserved2;          /* alignment pad, m.b.z. */
    p_cont_elem_t *p_cont_elem; // Heap-allocated array
} __attribute__((
                    packed)); // Disabling compiler alignment in favor of RPC alignment.

namespace RPC::PDU {
struct Bind {
    /* NOTE
       Modifying the properties below may break the casting algorithm.
       Adjust it accordingly.
    */

    /* common fields */
    u_int8 rpc_vers = 5;                               /* RPC version */
    u_int8 rpc_vers_minor = 0;                         /* minor version */
    Type PTYPE = Type::bind;                           /* bind PDU */
    u_int8 pfc_flags = PFC_FIRST_FRAG | PFC_LAST_FRAG; /* flags */
    byte packed_drep[4];     /* NDR data rep format label*/
    u_int16 frag_length;     /* total length of fragment */
    u_int16 auth_length = 0; /* length of auth_value */
    u_int32 call_id;         /* call identifier */
    /* end common fields */

    u_int16 max_xmit_frag;  /* max transmit frag size, bytes */
    u_int16 max_recv_frag;  /* max receive frag size, bytes */
    u_int32 assoc_group_id; /* incarnation of client-server assoc group */

    /* presentation context list */
    p_cont_list_t p_context_elem; /* variable size */

    inline Bind(const std::vector<byte> &rawPDU) {
        // Copy PDU fixed-size properties, including those nested in p_cont_list_t
        // type.
        memcpy(this,          // Copy into the beginning of this structure
               rawPDU.data(), // Copy from the beginning of the raw PDU
               offsetof(Bind, p_context_elem) + offsetof(p_cont_list_t, p_cont_elem)
               // Copy all fixed-size properties, including those nested in
               // p_cont_list_t type.
              );

        // Allocate array of p_cont_list_t->p_cont_elem_t on the heap
        p_context_elem.p_cont_elem = (p_cont_elem_t *)malloc(
                                         p_context_elem.n_context_elem * sizeof(p_cont_elem_t));

        // Iterate through p_cont_list_t->p_cont_elem_t elements
        p_cont_elem_t *CurrContElemPtr =
            (p_cont_elem_t *)(rawPDU.data() + offsetof(Bind, p_context_elem) +
                              offsetof(p_cont_list_t, p_cont_elem));
        for (int i = 0; i < p_context_elem.n_context_elem; i++) {
            memcpy(
                (void *)(&p_context_elem
                         .p_cont_elem[i]), // Copy into the heap-allocated array
                CurrContElemPtr, // Copy from the calculated offset in the raw PDU
                offsetof(p_cont_elem_t,
                         transfer_syntaxes) // Copy all fixed-size properties
            );

            // Allocate array of p_cont_list_t->p_cont_elem_t->p_syntax_id_t on the
            // heap
            p_context_elem.p_cont_elem[i].transfer_syntaxes = (p_syntax_id_t *)malloc(
                        p_context_elem.p_cont_elem[i].n_transfer_syn * sizeof(p_syntax_id_t));

            // Iterate through p_cont_list_t->p_cont_elem_t->p_syntax_id_t elements
            p_syntax_id_t *CurrSyntaxIdPtr =
                (p_syntax_id_t *)((byte *)CurrContElemPtr +
                                  offsetof(
                                      p_cont_elem_t,
                                      transfer_syntaxes)); // Pointer to the
            // transfer_syntaxes data
            for (int j = 0; j < p_context_elem.p_cont_elem[i].n_transfer_syn; j++) {
                memcpy(
                    (void *)(&p_context_elem.p_cont_elem[i]
                             .transfer_syntaxes[j]), // Copy into the
                    // heap-allocated array
                    CurrSyntaxIdPtr, // Copy from the calculated offset in the raw PDU
                    sizeof(p_syntax_id_t) // Copy all properties
                );

                CurrSyntaxIdPtr += 1; // Advance the pointer to the next p_syntax_id_t
            }

            // Set the next p_cont_list_t->p_cont_elem_t element
            CurrContElemPtr = (p_cont_elem_t *)CurrSyntaxIdPtr;
        }
    }

    ~Bind() {
        for (int i = 0; i < p_context_elem.n_context_elem; i++)
            free(p_context_elem.p_cont_elem[i].transfer_syntaxes);
        free(p_context_elem.p_cont_elem);
    }
} __attribute__((
                    packed)); // Disabling compiler alignment in favor of RPC alignment.
} // namespace RPC::PDU
