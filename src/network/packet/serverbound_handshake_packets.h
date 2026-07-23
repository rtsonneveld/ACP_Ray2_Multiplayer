#pragma once

/** Sent to the server to request a handshake. */
struct ServerboundRequestHandshakePacket {
	static constexpr uint16_t ID = 0;
	uint32_t temp;
};

template<typename S>
void serialize(S& s, ServerboundRequestHandshakePacket& p) {
	s.value4b(p.temp);
}

/** Sent to the server to confirm a transfer.. */
struct ServerboundConfirmTransferPacket {
	static constexpr uint16_t ID = 1;
	uint32_t temp;
};

template<typename S>
void serialize(S& s, ServerboundConfirmTransferPacket& p) {
	s.value4b(p.temp);
}