#pragma once

#include "../../util/vector.h"

/** Sent to the server to indicate a movement */
struct ServerboundMovePacket {
	static constexpr uint16_t ID = 0;
	Vec3 position;
};

template<typename S>
void serialize(S& s, ServerboundMovePacket& p) {
	s.object(p.position);
}