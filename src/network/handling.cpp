#include "network.h"
#include "../server/playermanager.h"
#include "packet/clientbound_play_packets.h"
#include "packet/serverbound_play_packets.h"

namespace R2MP {
	namespace NET {
		void HandlePlayClientbound(DecodedPacket& decoder) {
			switch (decoder.Id()) {
			case 0: {
				auto packet = decoder.Get<ClientboundPlayerAddPacket>();
				LOG::Print("[client] Received add player about %d called %s!", packet.playerId, packet.playerName.data());
				break;
			}
			case 1: {
				auto packet = decoder.Get<ClientboundPlayerRemovePacket>();
				LOG::Print("[client] Received remove player about %d!", packet.playerId);
				break;
			}
			case 2: {
				auto packet = decoder.Get<ClientboundPlayerPositionPacket>();
				LOG::Print("[client] Received player position!");
				break;
			}
			case 3: {
				auto packet = decoder.Get<ClientboundPlayerChangeLevelPacket>();
				LOG::Print("[client] Received player change level!");
				break;
			}
			case 4: {
				auto packet = decoder.Get<ClientboundLoginResponsePacket>();
				LOG::Print("[client] Received login response!");
				break;
			}
			}
		}

		void HandlePlayServerbound(uint32_t playerId, DecodedPacket& decoder) {
			switch (decoder.Id()) {
			case 0: {
				auto packet = decoder.Get<ServerboundMovePacket>();
				LOG::Print("[server] Received movement packet from %d!", playerId);
				break;
			}
			case 1: {
				auto packet = decoder.Get<ServerboundLoginPacket>();
				SER::GetPlayerManager().Initialize(playerId, packet.username);
				break;
			}
			}
		}
	};
};