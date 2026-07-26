#pragma once

#include "../util/vector.h"
#include "../network/network.h"
#include <unordered_map>

namespace R2MP {
	namespace SER {
		struct Player {
			uint32_t playerId;
			NET::NetworkConnection* connection;
			bool initialized;
			std::string username;
			Vec3 position;
			std::string levelName;
		};

		class PlayerManager {
		private:
			uint32_t lastPlayerId;
			std::unordered_map<uint32_t, Player> players;

		public:
			/** Adds a new player using the given connection. */
			uint32_t Add(NET::NetworkConnection* connection);

			/** Initializes the player with the given player id. */
			void Initialize(uint32_t playerId, std::string username, Vec3 position, std::string levelName);

			/** Broadcasts the given packet to all players. */
			template<typename T>
			void Broadcast(const T& packet) {
				auto encoded = EncodePacket(packet);
				for (const auto& [id, player] : players) {
					if (!player.initialized) continue;
					player.connection->SendEncoded(encoded);
				}
			}

			/** Broadcasts the given packet to all players except the given player id. */
			template<typename T>
			void BroadcastExcept(uint32_t playerId, const T& packet) {
				auto encoded = EncodePacket(packet);
				for (const auto& [id, player] : players) {
					if (!player.initialized) continue;
					if (id == playerId) continue;
					player.connection->SendEncoded(encoded);
				}
			}

			/** Sends the given packet to the given player. */
			template<typename T>
			void Send(uint32_t playerId, const T& packet) {
				if (!players.contains(playerId)) return;
				auto& player = players[playerId];
				if (!player.initialized) continue;
				player.connection->Send(packet);
			}

			/** Removes the player with the given id. */
			void Remove(uint32_t playerId);

			/** Returns the data for the player with the given id. */
			Player& Get(uint32_t playerId);
		};

		/** Returns the server's player manager. */
		PlayerManager& GetPlayerManager();
	};
}