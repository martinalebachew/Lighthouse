// response.cpp
// (C) Martin Alebachew, 2023

/*
This files defines the RPC response PDU wrapper struct.
*/

#include "response.hpp"

namespace RPC::PDU {
Response::Response(Request &request, std::vector<byte> responseStub) {
    // TODO: implement custom data representation that allows us to discard
    // endianess conversion when casting to a buffer For now, we'll copy the
    // data representation of the client, as specified in the bind PDU
    memcpy(packed_drep, request.packed_drep, 4);

    call_id = request.call_id; // This value is set by the client
    stub = responseStub;
}

std::vector<byte> Response::toBuffer() {
    frag_length = offsetof(Response, stub) + stub.size();
    alloc_hint = stub.size(); // Irrelevant since fragmented requests are not implemented

    std::vector<byte> buffer = std::vector<byte>(frag_length);
    memcpy(buffer.data(), this, offsetof(Response, stub));
    memcpy(buffer.data() + offsetof(Response, stub), stub.data(), stub.size());
    return buffer;
}
} // namespace RPC::PDU
