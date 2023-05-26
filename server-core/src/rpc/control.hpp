// control.hpp
// (C) Martin Alebachew, 2023

/*
This file contains RPC conversation control
wrapper.
*/

#pragma once
#include <iostream>
#include <vector>
#include <boost/asio.hpp>
#include "primitives.hpp"

#define HEAD_SIZE 10 // Frag length is specified in 9-10 bytes of CO PDUs (index 8-9)

namespace RPC::Control {
struct Conversation {
  std::vector<byte> ReceiveFragment(boost::asio::ip::tcp::socket &socket);
  std::vector<byte> ReceivePDU(boost::asio::ip::tcp::socket &socket);
  void SendFragment(boost::asio::ip::tcp::socket &socket, std::vector<byte> fragment);
  void SendPDU(boost::asio::ip::tcp::socket &socket, std::vector<byte> pdu);
};
} // namespace RPC::Control
