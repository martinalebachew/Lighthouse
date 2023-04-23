// control.cpp
// (C) Martin Alebachew, 2023

#pragma once
#include <boost/asio.hpp>
#include <iostream>
#include <vector>
#include "presentation.hpp"
#include "primitives.hpp"

namespace RPC::Control {
    class Conversation {
    public:
        std::vector<byte> ReceiveFragment(boost::asio::ip::tcp::socket &socket);
        std::vector<byte> ReceivePDU(boost::asio::ip::tcp::socket &socket);
    };
} // namespace RPC::Control