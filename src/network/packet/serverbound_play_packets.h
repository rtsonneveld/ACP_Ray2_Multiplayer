#pragma once

#include "../../util/vector.h"
#include "constants.h"

namespace R2MP {
	namespace NET {
		/** Sent to the server to indicate a movement */
		struct ServerboundMovePacket {
			static constexpr uint16_t ID = 0;
			Vec3 position;
		};

		template<typename S>
		void serialize(S& s, ServerboundMovePacket& p) {
			s.object(p.position);
		}

		/** Sent on login to authenticate and share username. */
		struct ServerboundLoginPacket {
			static constexpr uint16_t ID = 1;
			std::string username;
		};

		template<typename S>
		void serialize(S& s, ServerboundLoginPacket& p) {
			s.text1b(p.username, Constants::MAX_PLAYER_NAME_LENGTH);
		}
	};
};