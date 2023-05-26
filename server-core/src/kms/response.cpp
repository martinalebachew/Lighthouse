// response.cpp
// (C) Martin Alebachew, 2023

/*
This file defines the KMS response wrapper struct.
This file includes modified code from vlmcsd/kms.h by Wind4.
*/

#include "response.hpp"

static const BYTE DefaultHwId[8] = { 0x3A, 0x1C, 0x04, 0x96, 0x00, 0xB6, 0x00, 0x76 };

namespace KMS {
Response::Response(KMS::Request &request)
{
  memcpy(IV, &request.IV, 16); // Use request IV for response
  Version = request.Version;
  RawVersion = request.RawVersion;
  
  // TODO: Generate PID values
  PIDSize = 2*49; // 98 bytes
  byte pidexample[] = {0x35, 0x00, 0x35, 0x00, 0x30, 0x00, 0x34, 0x00, 0x31, 0x00, 0x2d, 0x00, 0x30, 0x00, 0x30, 0x00, 0x32, 0x00, 0x30, 0x00, 0x36, 0x00, 0x2d, 0x00, 0x35, 0x00, 0x35, 0x00, 0x35, 0x00, 0x2d, 0x00, 0x36, 0x00, 0x35, 0x00, 0x37, 0x00, 0x35, 0x00, 0x33, 0x00, 0x30, 0x00, 0x2d, 0x00, 0x30, 0x00, 0x33, 0x00, 0x2d, 0x00, 0x36, 0x00, 0x31, 0x00, 0x35, 0x00, 0x36, 0x00, 0x2d, 0x00, 0x37, 0x00, 0x36, 0x00, 0x30, 0x00, 0x31, 0x00, 0x2e, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x2d, 0x00, 0x32, 0x00, 0x31, 0x00, 0x33, 0x00, 0x32, 0x00, 0x30, 0x00, 0x31, 0x00, 0x39, 0x00, 0x00, 0x00};
  memcpy(KmsPID, pidexample, sizeof(pidexample));

  CMID = request.CMID; // This value is set by the client
  ClientTime = request.ClientTime; // This value is set by the client

  Count = request.N_Policy << 1;
  VLActivationInterval = 120;
  VLRenewalInterval = 10080;
}

std::vector<byte> Response::toEncryptedBuffer() {
  // Copy the response struct to a buffer
  size_t bufferSize = sizeof(Response) - sizeof(KmsPID) + PIDSize;
  std::vector<byte> buffer(bufferSize);

  memcpy(buffer.data(), this, offsetof(Response, KmsPID) + PIDSize);
  memcpy(buffer.data() + offsetof(Response, KmsPID) + PIDSize, &CMID, sizeof(Response) - offsetof(Response, CMID));

  // Calculate the size of the encrypted data in the buffer and the required padding
  size_t encryptSize = sizeof(Response) - offsetof(Response, IV) - sizeof(KmsPID) + PIDSize; // Number of bytes to encrypt
  size_t encryptPadding = 16 - (encryptSize % 16);

  // Add the padding to the buffer
  bufferSize += encryptPadding;
  buffer.resize(bufferSize);

  { // This scope marks EOL of the temporary pointers
    // Create temnporary pointers to the buffer
    Response* bufferStart = (Response*)buffer.data();
    byte* bufferIV = bufferStart->IV;

    byte* bufferEnd = buffer.data() + buffer.size() - encryptPadding;
    byte* bufferRandomXoredIVs = bufferEnd - (sizeof(Response) - offsetof(Response, RandomXoredIVs));
    byte* bufferHash = bufferRandomXoredIVs + sizeof(RandomXoredIVs);
    byte* bufferHwId = bufferHash + sizeof(Hash);
    byte* bufferXoredIVs = bufferHwId + sizeof(HwId);

    // Get random salt and SHA256 it
    get16RandomBytes(bufferRandomXoredIVs);
    Sha256(bufferRandomXoredIVs, sizeof(RandomXoredIVs), bufferHash);

    // Xor Random bytes with decrypted request IV
    XorBlock(IV, bufferRandomXoredIVs);

    // Copy decrypted request IV to buffer
    memcpy(bufferXoredIVs, IV, 16);

    // pre-fill with default HwId
    memcpy(bufferHwId, DefaultHwId, sizeof(HwId));

    // Generate random IV for encryption
    get16RandomBytes(bufferIV);

    // Generate HMAC
    if (!CreateV6Hmac(bufferIV, encryptSize, 0))
      throw std::runtime_error("HMAC creation failed.");

    // Encrypt the buffer
    AesCtx aesCtx;
    AesInitKey(&aesCtx, KeyV6);
    AesEncryptCbc(&aesCtx, bufferIV, &encryptSize);
  }

  // Add error code and set to zero to signal success
  buffer.resize(buffer.size() + 4);
  memset(buffer.data() + buffer.size() - 4, 0, 4);

  // Set the body length properties in the buffer
  Response* bufferStart = (Response*)buffer.data();
  bufferStart->bodyLength1 = encryptSize + 4;
  bufferStart->bodyLength2 = bufferStart->bodyLength1;

  return buffer;
}
} // namespace KMS