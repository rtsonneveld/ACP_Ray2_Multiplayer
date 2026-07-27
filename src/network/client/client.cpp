#include "client.h"

namespace R2MP {
	namespace NET {
		/** Implements a serverbound networking solution over ENet. */
		class ENetServerboundNetworking : public NetworkConnection {
		public:
			RaymanClient* client;

			void SendEncoded(EncodedPacket& packet) {
				client->Send(packet);
			}
		};

		void RaymanClient::Initialize() {
			client = enet_host_create(
				NULL, // NULL creates a client
				1, // Allow one connection
				2, // Use 2 channels
				0, // Do not limit bandwidth
				0
			);
			if (client == NULL) {
				LOG::Print("An error occurred while trying to create an ENet client.");
				exit(EXIT_FAILURE);
			}

			// Create a thread to poll the client for updates
			running = true;
			thread = std::thread(&RaymanClient::Tick, this);
			thread.detach();
		}

		void RaymanClient::Shutdown() {
			if (connected) {
				enet_peer_disconnect(peer, 0);
				Reset();
			}
			running = false;
			enet_host_destroy(client);
		}

		void RaymanClient::Reset() {
			enet_peer_reset(peer);
			connected = false;
			awaitDisconnect = 0;
		}

		void RaymanClient::Tick() {
			// Tick for events for at most 50ms before re-checking if the thread has been asked to stop
			ENetEvent event;
			while (running) {
				// Await connecting to the server
				if (awaitConnect) {
					awaitConnect = false;

					// Wait up to 5s to connect to the server
					if (enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
						connected = true;
						ENetServerboundNetworking networking;
						networking.client = this;
						SetServerboundConnection(&networking);
					} else {
						LOG::Print("Failed to connect to server");
						continue;
					}
				}

				// Ignore while disconnected and sleep
				if (!connected) {
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
					continue;
				}

				// Force close connection if we've exceeded the connection time
				if (awaitDisconnect > 0) {
					auto duration = std::chrono::system_clock::now().time_since_epoch();
					auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
					if (milliseconds >= awaitDisconnect) {
						Reset();
						continue;
					}
				}

				// Await a packet
				if (enet_host_service(client, &event, 20) > 0) {
					switch (event.type) {
					case ENET_EVENT_TYPE_RECEIVE: {
						auto decoded = DecodePacket(reinterpret_cast<uint8_t*>(event.packet->data), event.packet->dataLength, 0);
						std::lock_guard<std::mutex> lock(queueMutex);
						packetQueue.push(std::move(decoded));
						enet_packet_destroy(event.packet);
						break;
					}
					case ENET_EVENT_TYPE_DISCONNECT: {
						LOG::Print("Successfully disconnected from server, data=%u", event.data);
						enet_peer_reset(peer);
						connected = false;
						break;
					}
					}
				}
			}
		}

		void RaymanClient::Connect(std::string hostname, int port) {
			// Don't connect if already connected
			if (connected) {
				LOG::Print("Client is already connected to a server");
				return;
			}

			// Determine the target address
			ENetAddress address;
			enet_address_set_host(&address, hostname.c_str());
			address.port = port;

			// Initiate the connection
			peer = enet_host_connect(client, &address, 2, 0);
			if (peer == NULL) {
				LOG::Print("An error occurred while trying to connect to the ENet server.");
				exit(EXIT_FAILURE);
			}
			awaitConnect = true;
		}

		void RaymanClient::Disconnect() {
			if (!connected) return;

			// Gracefully tell the server we intend to disconnect
			LOG::Print("Informing server about disconnection");
			enet_peer_disconnect(peer, 0);

			// Store a time when we forcefully disconnect
			auto duration = std::chrono::system_clock::now().time_since_epoch();
			auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
			awaitDisconnect = milliseconds + 3000;
		}

		void RaymanClient::Send(EncodedPacket& packet) {
			if (!connected) {
				LOG::Print("Cannot send packet while not connected to server");
				return;
			}
			ENetPacket* enetPacket = enet_packet_create(packet.Get(), packet.Length(), ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, enetPacket);
		}

		bool RaymanClient::IsConnected() {
			return connected;
		}

		void RaymanClient::Poll() {
			std::lock_guard<std::mutex> lock(queueMutex);
			while (!packetQueue.empty()) {
				auto& decoder = packetQueue.front();
				HandlePlayClientbound(decoder);
				packetQueue.pop();
			}
		}

		std::unique_ptr<RaymanClient> CreateClient() {
			auto raymanClient = std::make_unique<RaymanClient>();
			raymanClient->Initialize();
			return raymanClient;
		}
	};
};