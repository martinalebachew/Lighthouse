// request.hpp
// (C) Martin Alebachew, 2023

/*
This file defines the KMS request wrapper struct.
This file includes modified code from vlmcsd/kms.h by Wind4.
*/

#include "request.hpp"

namespace KMS {
Request::Request(std::vector<byte> stub) {
  // Validate stub size
  if (stub.size() != sizeof(Request))
    throw std::runtime_error("Invalid stub size. Expected " +
                             std::to_string(sizeof(Request)) + " bytes, got " +
                             std::to_string(stub.size()) + " bytes.");

  // Copy all properties
  memcpy(this, stub.data(), sizeof(Request));

  // Decrypt stub encrypted properties
  AesCtx ctx;
  AesInitKey(&ctx, KeyV6);
  AesDecryptCbc(&ctx, IV, 256);

  // Validate decryption
  if (!!memcmp(&RawVersion, &Version, sizeof(VERSION)))
    throw std::runtime_error("Stub decryption failed.");

  // TODO: validate KMS version 6.0
}

std::string Request::GetWorkstationName() {
  std::string name = "";
  for (int i = 0; i < 64; i++) {
    if (WorkstationName[i] == 0)
      break;
    name += WorkstationName[i];
  }

  return name;
}
} // namespace KMS
