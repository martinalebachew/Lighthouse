// control.cpp
// (C) Martin Alebachew, 2023

/*
This file implements the RPC conversation control wrapper.
*/

#include "control.hpp"

namespace RPC::Control {
std::vector<byte> Conversation::ReceiveFragment(socket_t &socket) {
  std::vector<byte> PDU(HEAD_SIZE);
  boost::asio::read(socket, boost::asio::buffer(PDU));

  // TODO: Account for endianness specified in format label and
  // for host endianness. This only handles little endian to little endian.

  size_t size = *(u_int16*)(&PDU.at(HEAD_SIZE - 2));
  PDU.resize(size);
  std::cout << "[RPC] PDU Fragment Size: " << size << " bytes" << std::endl;

  // Receive rest of the PDU
  boost::asio::read(
    socket, boost::asio::buffer(PDU.data() + HEAD_SIZE * sizeof(PDU[0]), size - HEAD_SIZE)
  );
  return PDU;
}

std::vector<byte> Conversation::ReceivePDU(socket_t &socket) {
  // No support for fragmented PDUs
  return ReceiveFragment(socket); // TODO: Throw error if PDU is fragmented
}
} // namespace RPC::Control
