#pragma once

#include "../../util/vector.h"

/** Sent to the client to spawn a new player. */
struct ClientboundPlayerAddPacket {
	static constexpr uint16_t ID = 0;
	uint32_t playerId;
};

template<typename S>
void serialize(S& s, ClientboundPlayerAddPacket& p) {
	s.value4b(p.playerId);
}

/** Sent to the client to remove a player. */
struct ClientboundPlayerRemovePacket {
	static constexpr uint16_t ID = 1;
	uint32_t playerId;
};

template<typename S>
void serialize(S& s, ClientboundPlayerRemovePacket& p) {
	s.value4b(p.playerId);
}

/** Sent to the client with an updated player position. */
struct ClientboundPlayerPositionPacket {
	static constexpr uint16_t ID = 2;
	uint32_t playerId;
	Vec3 position;
};

template<typename S>
void serialize(S& s, ClientboundPlayerPositionPacket& p) {
	s.value4b(p.playerId);
	s.object(p.position);
}

/** Sent to the client when a player changes levels. */
struct ClientboundPlayerChangeLevelPacket {
	static constexpr uint16_t ID = 3;
	uint32_t playerId;
	uint16_t levelId;
	Vec3 position;
};

template<typename S>
void serialize(S& s, ClientboundPlayerChangeLevelPacket& p) {
	s.value4b(p.playerId);
	s.value2b(p.levelId);
	s.object(p.position);
}