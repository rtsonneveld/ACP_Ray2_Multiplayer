#include "server.h"
#include "../packet/serverbound_play_packets.h"

namespace R2MP {
	namespace NET {
		/** Implements a serverbound networking solution over ENet. */
		class ENetClientboundNetworking : public NetworkConnection {
		public:
			RaymanServer* server;
			ENetPeer* peer;

			void SendImpl(EncodedPacket& packet) {
				server->Send(peer, packet);
			}
		};

		/** Client data stored on ENet peer. */
		struct ClientData {
			uint32_t playerId;
		};

		void RaymanServer::Initialize(ENetAddress address) {
			// Create the server host itself
			server = enet_host_create(
				&address,
				64, // Allow up to 64 clients to be connected
				2, // Use 2 channels
				0, // Do not limit bandwidth
				0
			);
			if (server == NULL) {
				LOG::Print("An error occurred while trying to create an ENet server host.");
				exit(EXIT_FAILURE);
			}

			// Create a thread to poll the server for updates
			running = true;
			thread = std::thread(&RaymanServer::Tick, this);
			thread.detach();
			LOG::Print("Started new ENet server");
		}

		void RaymanServer::Tick() {
			// Tick for events for at most 50ms before re-checking if the thread has been asked to stop
			ENetEvent event;
			while (running) {
				if (enet_host_service(server, &event, 50) > 0) {
					switch (event.type) {
					case ENET_EVENT_TYPE_CONNECT: {
						// Create a new connection for this player
						ENetClientboundNetworking networking;
						networking.server = this;
						networking.peer = event.peer;
						ClientData* data = new ClientData;
						data->playerId = CreatePlayer(&networking);
						event.peer->data = data;
						break;
					}
					case ENET_EVENT_TYPE_RECEIVE: {
						ClientData* data = static_cast<ClientData*>(event.peer->data);
						if (data) {
							uint32_t playerId = data->playerId;
							auto decoded = DecodePacket(reinterpret_cast<uint8_t*>(event.packet->data), event.packet->dataLength, playerId);
							std::lock_guard<std::mutex> lock(queueMutex);
							packetQueue.push(std::move(decoded));
						}
						enet_packet_destroy(event.packet);
						break;
					}
					case ENET_EVENT_TYPE_DISCONNECT: {
						LOG::Print("Received disconnect request from %s:%d", event.peer->address.host, event.peer->address.port);
						break;
					}
					}
				}
			}
		}

		void RaymanServer::Shutdown() {
			// Destroy the ENet server
			running = false;
			enet_host_destroy(server);
		}

		template<typename T>
		void RaymanServer::Broadcast(EncodedPacket& encoded) {
			ENetPacket* enetPacket = enet_packet_create(encoded.Get(), encoded.Length(), ENET_PACKET_FLAG_RELIABLE);
			enet_host_broadcast(server, 0, enetPacket);
		}

		void RaymanServer::Send(ENetPeer* peer, EncodedPacket& encoded) {
			ENetPacket* enetPacket = enet_packet_create(encoded.Get(), encoded.Length(), ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, enetPacket);
		}

		void RaymanServer::Poll() {
			std::lock_guard<std::mutex> lock(queueMutex);
			while (!packetQueue.empty()) {
				auto& decoder = packetQueue.front();
				HandlePlayServerbound(decoder.PlayerId(), decoder);
				packetQueue.pop();
			}
		}

		std::unique_ptr<RaymanServer> CreateServer() {
			// Determine the address to host on, we always host on the same port on localhost.
			auto raymanServer = std::make_unique<RaymanServer>();
			ENetAddress address;
			address.host = ENET_HOST_ANY;
			address.port = DEFAULT_SERVER_PORT;
			raymanServer->Initialize(address);
			return raymanServer;
		}
	};
};