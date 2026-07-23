#pragma once

/** Sent to the client to confirm the handshake. */
struct ClientboundHandshakeConfirmPacket {
    static constexpr uint16_t ID = 0;
    uint32_t temp;
};

template<typename S>
void serialize(S& s, ClientboundHandshakeConfirmPacket& p) {
    s.value4b(p.temp);
}

/** Sent to the client to request transferring to the play protocol. */
struct ClientboundRequestTransferPacket {
    static constexpr uint16_t ID = 1;
    uint32_t temp;
};

template<typename S>
void serialize(S& s, ClientboundRequestTransferPacket& p) {
    s.value4b(p.temp);
}