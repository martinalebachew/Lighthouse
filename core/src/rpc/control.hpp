// control.hpp
// (C) Martin Alebachew, 2023

/*
This file defines the RPC conversation control wrapper.
*/

#pragma once
#include "primitives.hpp"
#include <boost/asio.hpp>
#include <iostream>
#include <vector>

using socket_t = boost::asio::ip::tcp::socket;

// Fragment length is specified in 9-10 bytes of CO PDUs
#define HEAD_SIZE 10

namespace RPC::Control {
struct Conversation {
  std::vector<byte> ReceiveFragment(socket_t &socket);
  std::vector<byte> ReceivePDU(socket_t &socket);
  void SendFragment(socket_t &socket, std::vector<byte> fragment);
  void SendPDU(socket_t &socket, std::vector<byte> pdu);
};
} // namespace RPC::Control
