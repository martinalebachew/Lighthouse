// server-core.hpp
// (C) Martin Alebachew, 2023

#pragma once
#include "RPC/control.hpp"
#include "RPC/PDU/bind.hpp"
#include "RPC/PDU/bind_ack.hpp"
#include "RPC/PDU/request.hpp"
#include "RPC/PDU/response.hpp"
#include "KMS/request.hpp"
#include "KMS/response.hpp"
#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;
using namespace RPC;

constexpr int port = 1688; // Default KMS port

int main(int argc, const char *argv[]);