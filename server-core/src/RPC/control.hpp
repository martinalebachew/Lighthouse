// control.hpp
// (C) Martin Alebachew, 2023

/*
This file contains RPC conversation control
wrapper.
*/

#include "primitives.hpp"
#define HEAD_SIZE 10 // Frag length is specified in 9-10 bytes of CO PDUs (index 8-9)

namespace RPC::Control {
    struct Conversation {
        std::vector<byte> inline ReceiveFragment(boost::asio::ip::tcp::socket &socket) {
            std::vector<byte> PDU(HEAD_SIZE);
            boost::asio::read(socket, boost::asio::buffer(PDU));

            // TODO: Account for endianness specified in format label and for host endianness This only handles little endian to little endian
            size_t size = *(u_int16 *) (&PDU.at(HEAD_SIZE - 2));
            PDU.resize(size);
            std::cout << "[RPC] PDU Fragment Size: " << size << " bytes" << std::endl;

            boost::asio::read(socket, boost::asio::buffer(PDU.data() + HEAD_SIZE * sizeof(PDU[0]),
                                                        size - HEAD_SIZE)); // Receive rest of the PDU
            return PDU;
        };

        std::vector<byte> inline ReceivePDU(boost::asio::ip::tcp::socket &socket) {
            // No support for fragmented PDUs
            return ReceiveFragment(socket); // TODO: Throw error if PDU is fragmented
        }
    };
}