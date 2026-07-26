#include "playermanager.h"
#include "../network/packet/clientbound_play_packets.h"

namespace R2MP {
	namespace SER {
		PlayerManager playerManager;

		uint32_t PlayerManager::Add(NET::NetworkConnection* connection) {
			lastPlayerId++;
			Vec3 initialPosition = Vec3{ 0.0, 0.0, 0.0 };
			Player player = Player{
				.data = {
					.playerId = lastPlayerId,
					.username = "Unknown",
					.position = initialPosition,
					.levelName = "Unknown",
				},
				.connection = connection,
				.initialized = false,
			};

			players[lastPlayerId] = player;
			return lastPlayerId;
		}

		void PlayerManager::Initialize(uint32_t playerId, std::string username, Vec3 position, std::string levelName) {
			if (!players.contains(playerId)) return;
			auto& player = players[playerId];
			player.initialized = true;
			player.data.username = username;
			player.data.position = position;
			player.data.levelName = levelName;
			LOG::Print("[server] Created new player with id %d called %s", lastPlayerId, username.data());

			// Send this player to everyone else, and everyone else to them!
			NET::ClientboundPlayerAddPacket packet{
					.playerId = playerId,
					.playerName = username,
					.position = position,
					.levelName = levelName
			};
			BroadcastExcept(playerId, packet);

			// Send information about everyone else to them
			for (const auto& [id, value] : players) {
				if (id == playerId) continue;
				if (!value.initialized) continue;
				NET::ClientboundPlayerAddPacket otherPacket{
					.playerId = id,
					.playerName = value.data.username,
					.position = position,
					.levelName = levelName
				};
				player.connection->Send(otherPacket);
			}
		}

		void PlayerManager::Remove(uint32_t playerId) {
			if (players.contains(playerId)) {
				auto& player = players[playerId];
				if (player.initialized) {
					// Ensure no further packets are sent!
					player.initialized = false;

					NET::ClientboundPlayerRemovePacket packet{
							.playerId = playerId
					};
					BroadcastExcept(playerId, packet);
				}

				// Free the player connection data
				delete player.connection;
			}
			players.erase(playerId);
		}

		Player& PlayerManager::Get(uint32_t playerId) {
			return players[playerId];
		}

		PlayerManager& GetPlayerManager() {
			return playerManager;
		}
	};
}