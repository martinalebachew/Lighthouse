// core.cpp
// (C) Martin Alebachew, 2023

#include "core.hpp"

int main(int argc, const char *argv[]) {
  bool interface = argc > 1 && argv[1] == (std::string)"interface";
  if (!interface) std::cout << "Lighthouse Core Module\n" << "By Martin Alebachew\n" << std::endl;
  else if (parseObjectFromStdin()["type"] != "ready") return -1;

  boost::asio::io_context io_context;
  tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), port));
  
  if (interface) {
    json listening = R"({"type":"listening"})"_json;
    flushObjectToStdout(listening);
  } else std::cout << "[TCP] Listening on port " << port << std::endl;

  while (true) { // TODO: replace iterative server with asynchronous server and lock stdout
    // 1. Establish TCP connection with client
    auto socket_ptr = std::make_shared<boost::asio::ip::tcp::socket>(io_context);
    tcp::endpoint peer_endpoint;
    acceptor.accept(*socket_ptr, peer_endpoint);
    if (!interface) std::cout << "\n[TCP] Accepted connection from " << peer_endpoint << std::endl;

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

    // 5. Send client info to GUI
    if (interface) {
      json clientInfo;
      clientInfo["type"] = "clientInfo";
      clientInfo["base64_message"] = wcharStringToBase64(kmsRequest.WorkstationName, sizeof(KMS::Request::WorkstationName));
      flushObjectToStdout(clientInfo);
    } else std::cout << "[TCP] Closed connection from " << peer_endpoint << std::endl;
  }

  // End-of-Process (EOP) termination message, NodeJS workaround
  // This allows us to make sure all output is passed to the GUI before termination
  json EOP = R"({"type": "EOP"})"_json;
  flushObjectToStdout(EOP);
  parseObjectFromStdin(); // Wait for any valid message for confirmation
  return 0;
}
