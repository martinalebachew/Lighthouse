// messaging.js
// (C) Martin Alebachew, 2023

const fs = require('fs');
const os = require('os');

function parseObjectFromStdin() {
  // Read message size as 32-bit integer from stdin, in host byte order
  const sizeBuffer = Buffer.allocUnsafe(4); // Unsafe = no memset-like behaviour
  if (fs.readSync(process.stdin.fd, sizeBuffer, 0, sizeBuffer.length) !== sizeBuffer.length) throw "Failed to read message size!";
  const messageSize = os.endianness() === "LE" ? sizeBuffer.readUInt32LE() : sizeBuffer.readUInt32BE();

  // Read rest of the message
  const stringBuffer = Buffer.allocUnsafe(messageSize);
  if (fs.readSync(process.stdin.fd, stringBuffer, 0, stringBuffer.length) !== stringBuffer.length) throw "Failed to read message string!";

  // Convert raw message bytes into string
  const messageString = stringBuffer.toString();
  
  // Parse JSON from string
  return JSON.parse(messageString);
}

function flushObjectToStdout(obj) {
  // Convert object to string and calculate size prefix
  const messageString = JSON.stringify(obj);
  const sizeBuffer = Buffer.allocUnsafe(4);
  os.endianness() === "LE" ? sizeBuffer.writeUInt32LE(messageString.length) : sizeBuffer.writeUInt32BE(messageString.length);

  // Print length and data to stdout
  fs.writeSync(process.stdout.fd, sizeBuffer);
  fs.writeSync(process.stdout.fd, messageString);
  
  // Note that no flush method is available on NodeJS that wouldn't close the pipe.
  // This might cause problems in the furute.
  // C/C++ equivalent - fflush(stdout);
}

module.exports = {
  "parseObjectFromStdin": parseObjectFromStdin,
  "flushObjectToStdout": flushObjectToStdout
}