// bind.hpp
// (C) Martin Alebachew, 2023

/*
This files defines the RPC bind PDU wrapper class.
*/

#pragma once
#include <cstring>
#include <cstdlib>
#include "../primitives.hpp"
#include "../presentation.hpp"
#include "type.hpp"

namespace RPC::PDU {
struct Bind {
    /* NOTE
     Modifying the properties below may break the casting algorithm.
     Adjust it accordingly.
    */

    /* common fields */
    u_int8 rpc_vers = 5; /* 00:01 RPC version */
    u_int8 rpc_vers_minor = 0; /* 01:01 minor version */
    u_int8 PTYPE = (u_int8)Type::bind; /* 02:01 bind PDU */
    u_int8 pfc_flags; /* 03:01 flags */
    byte packed_drep[4]; /* 04:04 NDR data rep format label*/
    u_int16 frag_length; /* 08:02 total length of fragment */
    u_int16 auth_length = 0; /* 10:02 length of auth_value */
    u_int32 call_id; /* 12:04 call identifier */
    /* end common fields */

    u_int16 max_xmit_frag; /* 16:02 max transmit frag size, bytes */
    u_int16 max_recv_frag; /* 18:02 max receive frag size, bytes */
    u_int32 assoc_group_id; /* 20:04 incarnation of client-server assoc group */

    /* presentation context list */
    p_cont_list_t p_context_elem; /* variable size */

    inline Bind(const std::vector<char>& rawPDU) {
        // Copy PDU fixed-size properties, including those nested in p_cont_list_t type.
        memcpy(this, // Copy into the beginning of this structure
               rawPDU.data(), // Copy from the beginning of the raw PDU
               offsetof(Bind, p_context_elem) + offsetof(p_cont_list_t, p_cont_elem)
               // Copy all fixed-size properties, including those nested in p_cont_list_t type.
               );

        // Allocate array of p_cont_list_t->p_cont_elem_t on the heap
        p_context_elem.p_cont_elem = (p_cont_elem_t*)malloc(p_context_elem.n_context_elem * sizeof(p_cont_elem_t));

        // Iterate through p_cont_list_t->p_cont_elem_t elements
        p_cont_elem_t* CurrContElemPtr = (p_cont_elem_t*)(rawPDU.data() + offsetof(Bind, p_context_elem) + offsetof(p_cont_list_t, p_cont_elem));
        for (int i = 0; i < p_context_elem.n_context_elem; i++) {
            memcpy((void*)(&p_context_elem.p_cont_elem[i]), // Copy into the heap-allocated array
                   CurrContElemPtr, // Copy from the calculated offset in the raw PDU
                   offsetof(p_cont_elem_t, transfer_syntaxes) // Copy all fixed-size properties
                   );

            // Allocate array of p_cont_list_t->p_cont_elem_t->p_syntax_id_t on the heap
            p_context_elem.p_cont_elem[i].transfer_syntaxes = (p_syntax_id_t*)malloc(p_context_elem.p_cont_elem[i].n_transfer_syn * sizeof(p_syntax_id_t));

            // Iterate through p_cont_list_t->p_cont_elem_t->p_syntax_id_t elements
            p_syntax_id_t* CurrSyntaxIdPtr = (p_syntax_id_t*)((byte*)CurrContElemPtr + offsetof(p_cont_elem_t, transfer_syntaxes)); // Pointer to the transfer_syntaxes data
            for (int j = 0; j < p_context_elem.p_cont_elem[i].n_transfer_syn; j++) {
                memcpy((void*)(&p_context_elem.p_cont_elem[i].transfer_syntaxes[j]), // Copy into the heap-allocated array
                       CurrSyntaxIdPtr, // Copy from the calculated offset in the raw PDU
                       sizeof(p_syntax_id_t) // Copy all properties
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
} __attribute__ ((packed)); // Disabling compiler alignment in favor of RPC alignment.
} // namespace RPC::PDU