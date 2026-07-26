#pragma once

#include "../../util/vector.h"
#include <bitsery/traits/array.h>
#include "constants.h"
#include <array>

namespace R2MP {
	namespace NET {
		/** Sent to the server to indicate a movement. */
		struct ServerboundMovePacket {
			static constexpr uint16_t ID = 0;
			Vec3 position;
			std::array<ByteVec3, Constants::GHOST_NUMBONES> ghostBonePositions;
		};

		template<typename S>
		void serialize(S& s, ServerboundMovePacket& p) {
			s.object(p.position);
			s.container(p.ghostBonePositions);
		}

		/** Sent on login to authenticate and share username. */
		struct ServerboundLoginPacket {
			static constexpr uint16_t ID = 1;
			std::string username;
			Vec3 position;
			std::string levelName;
		};

		template<typename S>
		void serialize(S& s, ServerboundLoginPacket& p) {
			s.text1b(p.username, Constants::MAX_PLAYER_NAME_LENGTH);
			s.object(p.position);
			s.text1b(p.levelName, Constants::MAX_LEVEL_NAME_LENGTH);
		}

		/** Sent to the server to indicate a level switch. */
		struct ServerboundChangeLevelPacket {
			static constexpr uint16_t ID = 2;
			std::string levelName;
		};

		template<typename S>
		void serialize(S& s, ServerboundChangeLevelPacket& p) {
			s.text1b(p.levelName, Constants::MAX_LEVEL_NAME_LENGTH);
		}
	};
};