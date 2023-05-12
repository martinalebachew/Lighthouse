// control.hpp
// (C) Martin Alebachew, 2023

/*
This file contains RPC conversation control
wrapper.
*/

#include "primitives.hpp"
#define HEAD_SIZE                                                              \
  10 // Frag length is specified in 9-10 bytes of CO PDUs (index 8-9)

namespace RPC::Control {
struct Conversation {
  std::vector<byte> inline ReceiveFragment(
      boost::asio::ip::tcp::socket &socket) {
    std::vector<byte> fragment(HEAD_SIZE);
    boost::asio::read(socket, boost::asio::buffer(fragment));

    // TODO: Account for endianness specified in format label and for host
    // endianness This only handles little endian to little endian
    size_t size = *(u_int16 *)(&fragment.at(HEAD_SIZE - 2));
    fragment.resize(size);
    std::cout << "[RPC] <<< PDU Size: " << size << " bytes" << std::endl;

    boost::asio::read(
        socket,
        boost::asio::buffer(fragment.data() + HEAD_SIZE * sizeof(fragment[0]),
                            size - HEAD_SIZE)); // Receive rest of the fragment
    return fragment;
  };

  std::vector<byte> inline ReceivePDU(boost::asio::ip::tcp::socket &socket) {
    // No support for fragmented PDUs
    return ReceiveFragment(
        socket); // TODO: Throw error if PDU is fragmented (check flags)
  }

  void inline SendFragment(boost::asio::ip::tcp::socket &socket,
                           std::vector<byte> fragment) {
    std::cout << "[RPC] >>> PDU Size: " << fragment.size() << " bytes" << std::endl;
    boost::asio::write(socket, boost::asio::buffer(fragment));
  }

  void inline SendPDU(boost::asio::ip::tcp::socket &socket,
                      std::vector<byte> pdu) {
    // No support for fragmented PDUs
    SendFragment(socket, pdu);
  }
};
} // namespace RPC::Control
