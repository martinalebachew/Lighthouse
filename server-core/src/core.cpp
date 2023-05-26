// core.cpp
// (C) Martin Alebachew, 2023

#include "core.hpp"

int main(int argc, const char *argv[]) {
  std::cout << "Lighthouse Server Core\n"
            << "By Martin Alebachew\n"
            << std::endl;

  boost::asio::io_context io_context;
  tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), port));
  std::cout << "[TCP] Listening on port " << port << std::endl;

  while (true) { // TODO: replace iterative server with asynchronous server
    // 1. Establish TCP connection with client
    auto socket_ptr =
        std::make_shared<boost::asio::ip::tcp::socket>(io_context);
    tcp::endpoint peer_endpoint;
    acceptor.accept(*socket_ptr, peer_endpoint);
    std::cout << "\n[TCP] Accepted connection from " << peer_endpoint
              << std::endl;

    // 2. RPC-Bind with the client
    Control::Conversation conversation;

    // TODO: Implement and replace with conversation.Bind();
    PDU::Bind bind = conversation.ReceivePDU(*socket_ptr);
    PDU::BindAck bindAck = PDU::BindAck(bind, port);
    conversation.SendPDU(*socket_ptr, bindAck.toBuffer());

    // 3. Parse client's request
    PDU::Request request = conversation.ReceivePDU(*socket_ptr);
    KMS::Request kmsRequest = KMS::Request(request.stub);

    // 4. Build and send proper response
    auto kmsResponse = KMS::Response(kmsRequest);
    PDU::Response response(request, kmsResponse.toEncryptedBuffer());
    conversation.SendPDU(*socket_ptr, response.toBuffer());

    socket_ptr->close();
    std::cout << "[TCP] Closed connection from " << peer_endpoint << std::endl;
  }
}
