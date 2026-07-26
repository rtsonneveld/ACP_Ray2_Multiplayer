#pragma once
#include "../util/vector.h"
#include "../constants.h"
#include <string>
#include <array>

namespace R2MP {
	// Player data that is used both by the server and by the client
	struct CommonPlayerData {
		uint32_t playerId;
		std::string username;
		Vec3 position;
		std::array<ByteVec3, Constants::GHOST_NUMBONES> ghostBonePositions;
		std::string levelName;
	};

	template<typename S>
	void serialize(S& s, CommonPlayerData& d) {
		s.value4b(d.playerId);
		s.text1b(d.username, Constants::MAX_PLAYER_NAME_LENGTH);
		s.object(d.position);
		s.object(d.ghostBonePositions);
		s.text1b(d.levelName, Constants::MAX_LEVEL_NAME_LENGTH);
	}
}