// core.hpp
// (C) Martin Alebachew, 2023

/*
This file defines the enrty point for Lighthouse KMS server.
*/

#pragma once
#include "database/database.hpp"
#include "kms/request.hpp"
#include "kms/response.hpp"
#include "rpc/control.hpp"
#include "rpc/pdu/bind.hpp"
#include "rpc/pdu/bind_ack.hpp"
#include "rpc/pdu/request.hpp"
#include "rpc/pdu/response.hpp"
#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;
using namespace RPC;

constexpr int port = 1688; // Default KMS port

int main(int argc, const char* argv[]);
