#pragma once

/** Sent to peer to start the handshake. */
struct HandshakeIntroductionPacket {
    static constexpr uint16_t ID = 0;
    std::string username;
    long long bootTime;
    bool isServer;
};

template<typename S>
void serialize(S& s, HandshakeIntroductionPacket& p) {
    s.text1b(p.username, 64);
    s.value8b(p.bootTime);
    s.value1b(p.isServer);
}

/** Sent to peer to request transferring to the play protocol. */
struct RequestTransferPacket {
    static constexpr uint16_t ID = 1;
    std::string host;
};

template<typename S>
void serialize(S& s, RequestTransferPacket& p) {
    s.text1b(p.host, 64);
}