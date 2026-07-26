#include "network.h"
#include "../client/playermanager.h"
#include "../server/playermanager.h"
#include "packet/clientbound_play_packets.h"
#include "packet/serverbound_play_packets.h"

namespace R2MP {
	namespace NET {
		void HandlePlayClientbound(DecodedPacket& decoder) {
			switch (decoder.Id()) {
			case 0: {
				auto packet = decoder.Get<ClientboundPlayerAddPacket>();
				CLI::GetPlayerManager().Add(packet.playerId, packet.playerName, packet.position, packet.levelName);
				break;
			}
			case 1: {
				auto packet = decoder.Get<ClientboundPlayerRemovePacket>();
				CLI::GetPlayerManager().Remove(packet.playerId);
				break;
			}
			case 2: {
				auto packet = decoder.Get<ClientboundPlayerPositionPacket>();
				auto& player = CLI::GetPlayerManager().Get(packet.playerId);
				player.data.position = packet.position;
				break;
			}
			case 3: {
				auto packet = decoder.Get<ClientboundPlayerChangeLevelPacket>();
				auto& player = CLI::GetPlayerManager().Get(packet.playerId);
				player.data.levelName = packet.levelName;
				break;
			}
			case 4: {
				auto packet = decoder.Get<ClientboundLoginResponsePacket>();
				CLI::GetPlayerManager().SetPlayerId(packet.playerId);
				break;
			}
			}
		}

		void HandlePlayServerbound(uint32_t playerId, DecodedPacket& decoder) {
			switch (decoder.Id()) {
			case 0: {
				auto packet = decoder.Get<ServerboundMovePacket>();
				auto& player = SER::GetPlayerManager().Get(playerId);
				player.data.position = packet.position;
				NET::ClientboundPlayerPositionPacket outPacket{
					.playerId = playerId,
					.position = packet.position
				};
				SER::GetPlayerManager().BroadcastExcept(playerId, outPacket);
				break;
			}
			case 1: {
				auto packet = decoder.Get<ServerboundLoginPacket>();
				SER::GetPlayerManager().Initialize(playerId, packet.username, packet.position, packet.levelName);
				break;
			}
			case 2: {
				auto packet = decoder.Get<ServerboundChangeLevelPacket>();
				auto& player = SER::GetPlayerManager().Get(playerId);
				player.data.levelName = packet.levelName;
				NET::ClientboundPlayerChangeLevelPacket outPacket{
					.playerId = playerId,
					.levelName = packet.levelName
				};
				SER::GetPlayerManager().BroadcastExcept(playerId, outPacket);
				break;
			}
			}
		}
	};
};