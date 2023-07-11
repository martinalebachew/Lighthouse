// core.hpp
// (C) Martin Alebachew, 2023

#pragma once
#include "rpc/control.hpp"
#include "rpc/pdu/bind.hpp"
#include "rpc/pdu/bind_ack.hpp"
#include "rpc/pdu/request.hpp"
#include "rpc/pdu/response.hpp"
#include "kms/request.hpp"
#include "kms/response.hpp"
#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;
using namespace RPC;

constexpr int port = 1688; // Default KMS port
constexpr int LineWidth = 54; // Summary Section

std::string operator*(std::string rep, int n);
int main(int argc, const char *argv[]);