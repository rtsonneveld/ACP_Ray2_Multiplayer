#include "playermanager.h"

namespace R2MP {
	namespace CLI {
		PlayerManager playerManager;

		void PlayerManager::SetPlayerId(uint32_t playerId) {
			myPlayerId = playerId;
		}

		void PlayerManager::Add(uint32_t playerId, std::string username, Vec3 position, std::string levelName) {
			Player player = Player{
				.data = {
					.playerId = playerId,
					.username = username,
					.position = position,
					.levelName = levelName
				}
			};
			players[playerId] = player;
		}

		void PlayerManager::Remove(uint32_t playerId) {
			players.erase(playerId);
		}

		Player& PlayerManager::Get(uint32_t playerId) {
			return players[playerId];
		}

		std::vector<Player> PlayerManager::GetPlayers() {
			std::vector<Player> result;
			result.reserve(players.size());
			for (const auto& [id, player] : players) {
				result.push_back(player);
			}
			return result;
		}

		PlayerManager& GetPlayerManager() {
			return playerManager;
		}
	};
}