// core.cpp
// (C) Martin Alebachew, 2023

#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;
#define PORT 1688 // Default KMS host port

int main(int argc, const char* argv[]) {
  std::cout
    << "Lighthouse Core\n"
    << "(C) Martin Alebachew, 2023\n"
    << std::endl;

  boost::asio::io_context ioContext;
  tcp::acceptor acceptor(ioContext, tcp::endpoint(tcp::v4(), PORT));
  std::cout << "[TCP] Listening on port " << PORT << std::endl;

  while (true) { // TODO: Replace iterative server with asynchronous server
    // Establish TCP connection with client
    auto socketPtr = std::make_shared<boost::asio::ip::tcp::socket>(ioContext);
    tcp::endpoint peerEndpoint;
    acceptor.accept(*socketPtr, peerEndpoint);
    std::cout << "[TCP] Accepted connection from " << peerEndpoint << std::endl;

    socketPtr->close();
    std::cout << "[TCP] Closed connection from " << peerEndpoint << std::endl;
  }

  return 0;
}
