// core.cpp
// (C) Martin Alebachew, 2023

/*
This file implements the enrty point for Lighthouse KMS server.
*/

#include "core.hpp"

std::string operator*(std::string rep, int n) {
  if (n < 0) return rep;
  std::string output = "";
  while (n--) output += rep;
  return output;
}

int main(int argc, const char* argv[]) {
  std::cout
    << "Lighthouse Core\n"
    << "(C) Martin Alebachew, 2023\n"
    << std::endl;

  Database database("../../KMSData.xml");
  std::cout << "[XML] Database loaded." << std::endl;

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

    // Print client information summary
    constexpr int LineWidth = 54;
    std::stringstream peerStream;
    peerStream << peerEndpoint;
    std::string peerString = peerStream.str();
    std::string paddingString = (std::string) "=" * ((LineWidth - peerString.size() - 2) / 2);
    std::string peerHeader = paddingString + " " + peerString + " " + paddingString;

    std::cout
      << "\n" << peerHeader << "\n"
      << "Edition:         " << database.getEditionBySkuID(kmsRequest.ActID) << "\n"
      << "Machine Name:    " << kmsRequest.GetWorkstationName() << "\n"
      << "Machine ID:      " << kmsRequest.CMID.toString() << "\n"
      << "KMS Version:     " << "6.0" << "\n"
      << "Virtual Machine: " << (kmsRequest.VMInfo ? "Yes" : "No") << "\n"
      << (std::string) "=" * peerHeader.size() << "\n";
  }

  return 0;
}
