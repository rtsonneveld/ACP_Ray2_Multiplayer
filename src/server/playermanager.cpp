#include "playermanager.h"
#include "../network/packet/clientbound_play_packets.h"

namespace R2MP {
	namespace SER {
		PlayerManager playerManager;

		uint32_t PlayerManager::Add(NET::NetworkConnection* connection) {
			lastPlayerId++;
			Player player = Player{
				.playerId = lastPlayerId,
				.connection = connection,
				.initialized = false,
				.username = "Unknown"
			};
			players[lastPlayerId] = player;
			return lastPlayerId;
		}

		void PlayerManager::Initialize(uint32_t playerId, std::string username) {
			if (!players.contains(playerId)) return;
			auto& player = players[playerId];
			player.initialized = true;
			player.username = username;
			LOG::Print("[server] Created new player with id %d called %s", lastPlayerId, username.data());

			// Send this player to everyone else, and everyone else to them!
			NET::ClientboundPlayerAddPacket packet{
					.playerId = playerId,
					.playerName = username
			};
			BroadcastExcept(playerId, packet);

			// Send information about everyone else to them
			for (const auto& [id, value] : players) {
				if (id == playerId) continue;
				if (!value.initialized) continue;
				NET::ClientboundPlayerAddPacket otherPacket{
					.playerId = id,
					.playerName = value.username
				};
				player.connection->Send(otherPacket);
			}
		}

		template<typename T>
		void PlayerManager::Broadcast(const T& packet) {
			auto encoded = EncodePacket(packet);
			for (const auto& [id, player] : players) {
				if (!player.initialized) continue;
				player.connection->SendEncoded(encoded);
			}
		}

		template<typename T>
		void PlayerManager::BroadcastExcept(uint32_t playerId, const T& packet) {
			auto encoded = EncodePacket(packet);
			for (const auto& [id, player] : players) {
				if (!player.initialized) continue;
				if (id == playerId) continue;
				player.connection->SendEncoded(encoded);
			}
		}

		template<typename T>
		void PlayerManager::Send(uint32_t playerId, const T& packet) {
			if (!players.contains(playerId)) return;
			auto& player = players[playerId];
			if (!player.initialized) continue;
			player.connection->Send(packet);
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

		PlayerManager& GetPlayerManager() {
			return playerManager;
		}
	};
}