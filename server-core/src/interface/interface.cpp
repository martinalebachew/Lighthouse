// interface.cpp
// (C) Martin Alebachew, 2023

#include "interface.hpp"

json parseObjectFromStdin() {
  // Read message size as 32-bit unsigned integer from stdin, in host byte order
  unsigned int messageSize;
  std::cin.read((char*)&messageSize, sizeof(typeof messageSize));

  // Read rest of the message
  std::vector<char> rawMessage(messageSize);
  std::cin.read(rawMessage.data(), rawMessage.size());

  // Convert raw message bytes into string
  std::string messageString(rawMessage.data(), rawMessage.size());

  // Parse JSON from string
  return json::parse(messageString);
}

void flushObjectToStdout(json &object) {
  // Convert object to string and calculate size prefix
  std::string messageString = object.dump();
  unsigned int messageSize = messageString.size();

  // Print length and data to stdout
  for (int i = 0; i < sizeof(typeof messageSize); i++)
    std::cout << *((unsigned char*)&messageSize + i);
  std::cout << messageString;

  fflush(stdout);
}