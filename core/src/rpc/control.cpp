// control.cpp
// (C) Martin Alebachew, 2023

/*
This file implements the RPC conversation control wrapper.
*/

#include "control.hpp"

namespace RPC::Control {
std::vector<byte> Conversation::ReceiveFragment(socket_t &socket) {
  std::vector<byte> fragment(HEAD_SIZE);
  boost::asio::read(socket, boost::asio::buffer(fragment));

  // TODO: Account for endianness specified in format label and
  // for host endianness. This only handles little endian to little endian.

  size_t size = *(u_int16*)(&fragment.at(HEAD_SIZE - 2));
  fragment.resize(size);
  std::cout << "[RPC] PDU Fragment Size: " << size << " bytes" << std::endl;

  // Receive rest of the fragment
  boost::asio::read(
    socket,
    boost::asio::buffer(fragment.data() + HEAD_SIZE * sizeof(fragment[0]), size - HEAD_SIZE)
  );
  return fragment;
}

std::vector<byte> Conversation::ReceivePDU(socket_t &socket) {
  // No support for fragmented PDUs
  return ReceiveFragment(socket); // TODO: Throw error if PDU is fragmented
}

void Conversation::SendFragment(socket_t &socket, std::vector<byte> fragment) {
  boost::asio::write(socket, boost::asio::buffer(fragment));
}

void Conversation::SendPDU(socket_t &socket, std::vector<byte> pdu) {
  // No support for fragmented PDUs
  SendFragment(socket, pdu);
}
} // namespace RPC::Control
