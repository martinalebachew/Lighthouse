// main.cpp
// (C) Martin Alebachew, 2023

#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
#define PORT 1688 // Default KMS host port

int main(int argc, const char *argv[])
{
    std::cout << "Lighthouse Server Core\n"
              << "By Martin Alebachew\n"
              << std::endl;

    boost::asio::io_context io_context;
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), PORT));
    std::cout << "[TCP] Listening on port " << PORT << std::endl;

    while (true) // TODO: replace iterative server with asynchronous server
    {
        // 1. Establish TCP connection with client
        tcp::socket socket(io_context);
        tcp::endpoint peer_endpoint;
        acceptor.accept(socket, peer_endpoint);
        std::cout << "[TCP] Accepted connection from " << peer_endpoint << std::endl;

        socket.close();
        std::cout << "[TCP] Closed connection from " << peer_endpoint << std::endl;
    }

    return 0;
}
