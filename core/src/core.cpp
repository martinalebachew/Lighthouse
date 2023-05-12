// core.cpp
// (C) Martin Alebachew, 2023

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

int main(int argc, const char* argv[]) {
  std::cout
    << "Lighthouse Core\n"
    << "(C) Martin Alebachew, 2023\n"
    << std::endl;

  boost::asio::io_context ioContext;
  tcp::acceptor acceptor(ioContext, tcp::endpoint(tcp::v4(), port));
  std::cout << "[TCP] Listening on port " << port << std::endl;

  while (true) { // TODO: Replace iterative server with asynchronous server
    // Establish TCP connection with client
    auto socketPtr = std::make_shared<boost::asio::ip::tcp::socket>(ioContext);
    tcp::endpoint peerEndpoint;
    acceptor.accept(*socketPtr, peerEndpoint);
    std::cout << "\n[TCP] Accepted connection from " << peerEndpoint << std::endl;

    // RPC-Bind with the client
    Control::Conversation conversation;

    // TODO: Implement and replace with conversation.Bind();
    PDU::Bind bind = conversation.ReceivePDU(*socketPtr);
    PDU::BindAck bindAck = PDU::BindAck(bind, port);
    conversation.SendPDU(*socketPtr, bindAck.toBuffer());

    // Parse client's request
    PDU::Request request = conversation.ReceivePDU(*socketPtr);
    KMS::Request kmsRequest = KMS::Request(request.stub);

    // Build and send proper response
    auto kmsResponse = KMS::Response(kmsRequest);
    PDU::Response response(request, kmsResponse.toEncryptedBuffer());
    conversation.SendPDU(*socketPtr, response.toBuffer());

    socketPtr->close();
    std::cout << "[TCP] Closed connection from " << peerEndpoint << std::endl;
  }

  return 0;
}
