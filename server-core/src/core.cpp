// core.cpp
// (C) Martin Alebachew, 2023

#include "core.hpp"

std::string operator*(std::string rep, int n) {
  if (n < 0) return rep;
  std::string output = "";
  while (n--) output += rep;
  return output;
}

int main(int argc, const char *argv[]) {
  std::cout << "Lighthouse Server Core\n"
            << "(C) Martin Alebachew, 2023\n"
            << std::endl;

  Database database("../../KMSData.xml");
  std::cout << "[XML] Database loaded." << std::endl;

  boost::asio::io_context ioContext;
  tcp::acceptor acceptor(ioContext, tcp::endpoint(tcp::v4(), port));
  std::cout << "[TCP] Listening on port " << port << std::endl;

  while (true) { // TODO: replace iterative server with asynchronous server
    // 1. Establish TCP connection with client
    auto socket_ptr = std::make_shared<boost::asio::ip::tcp::socket>(ioContext);
    tcp::endpoint peerEndpoint;
    acceptor.accept(*socket_ptr, peerEndpoint);
    std::cout << "\n[TCP] Accepted connection from " << peerEndpoint << std::endl;

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
    std::cout << "[TCP] Closed connection from " << peerEndpoint << std::endl;

    // 5. Print client information summary
    std::stringstream peerStream;
    peerStream << peerEndpoint;
    std::string peerString = peerStream.str();
    std::string paddingString = (std::string)"=" * ((LineWidth - peerString.size() - 2) / 2);
    std::string peerHeader = paddingString + " " + peerString + " " + paddingString;

    std::cout << "\n" << peerHeader << "\n"
              << "Edition:         " << database.getEditionBySkuID(kmsRequest.ActID) << "\n"
              << "Machine Name:    " << kmsRequest.GetWorkstationName() << "\n"
              << "Machine ID:      " << kmsRequest.CMID.toString() << "\n"
              << "KMS Version:     " << "6.0" << "\n"
              << "Virtual Machine: " << (kmsRequest.VMInfo ? "Yes" : "No") << "\n"
              << (std::string)"=" * peerHeader.size() << "\n";
  }
}
