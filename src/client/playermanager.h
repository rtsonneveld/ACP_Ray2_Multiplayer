#pragma once

#include "../util/vector.h"
#include "../network/network.h"
#include "../constants.h"
#include "../common/playerdata.h"
#include <unordered_map>

namespace R2MP {
	namespace CLI {
		struct Player {
			CommonPlayerData data;
		};

		class PlayerManager {
		private:
			uint32_t myPlayerId;
			std::unordered_map<uint32_t, Player> players;

		public:
			/** Sets the id of the local player. */
			void SetPlayerId(uint32_t playerId);

			/** Adds a new player under the given name. */
			void Add(uint32_t playerId, std::string username, Vec3 position, std::string levelName);

			/** Removes the player with the given id. */
			void Remove(uint32_t playerId);

			/** Returns the data for the player with the given id. */
			Player& Get(uint32_t playerId);

			/** Returns all players known to this manager. */
			std::vector<Player> GetPlayers();
		};

		/** Returns the client's player manager. */
		PlayerManager& GetPlayerManager();
	};
}