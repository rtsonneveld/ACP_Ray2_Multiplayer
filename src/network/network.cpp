#include "network.h"
#include "client/client.h"
#include "server/server.h"
#include "peer/peer.h"
#include "packet/serverbound_play_packets.h"

namespace R2MP {
	namespace NET {
		std::unique_ptr<P2PConnection> p2p;
		std::unique_ptr<RaymanClient> client;
		std::unique_ptr<RaymanServer> server;
		NetworkConnection* serverbound;
		NetworkState state = NetworkState::NONE;
		std::string username = "User";
		long long bootTime = 0;

		NetworkConnection* GetServerboundConnection() {
			return serverbound;
		}

		void SetServerboundConnection(NetworkConnection* networking) {
			// Update the stored connection and immediately send a packet with the username
			// to authenticate ourselves!
			serverbound = networking;
			ServerboundLoginPacket packet{
					.username = GetUsername()
			};
			networking->Send(packet);
			LOG::Print("Succesfully connected to server");
		}

		uint32_t CreatePlayer(NetworkConnection* networking) {
			if (server == nullptr) {
				LOG::Print("Cannot create client connections when not running server");
				return 0;
			}
			// TODO Implement client management on server
			return 0;
		}

		void RemovePlayer(uint32_t playerId) {

		}

		bool IsRunningServer() {
			return server != nullptr;
		}

		std::string GetUsername() {
			return username;
		}

		void SetUsername(std::string name) {
			if (name.length() >= 64) {
				LOG::Print("Invalid username, cannot exceed 64 characters!");
				return;
			}
			username = name;
			FILE* f = fopen("mp_settings.conf", "wb");
			if (f) {
				size_t len = username.size();
				fwrite(&len, sizeof(len), 1, f);
				fwrite(username.data(), 1, len, f);
				fclose(f);
			}
			LOG::Print("Username is now: %s", username.data());
		}

		long long GetBootTime() {
			return bootTime;
		}

		NetworkState GetState() {
			return state;
		}

		void ResetState() {
			// Destroy any created connections and reset to none so we can restart the process
			if (p2p != nullptr) {
				p2p->Destroy();
				p2p = nullptr;
			}
			state = NetworkState::NONE;
		}

		bool SetState(NetworkState from, NetworkState to) {
			// Update the state if it's coming from the correct one and debug print about it
			if (state != from) return false;
			state = to;
			return true;
		}

		void Initialize(EnumTestMode testMode) {
			// Initialize the ENet connectivity
			if (enet_initialize() != 0) {
				fprintf(stderr, "An error occurred while initializing ENet.\n");
				exit(EXIT_FAILURE);
			}
			atexit(enet_deinitialize);

			// Load the username from the settings and apply it
			FILE* f = fopen("mp_settings.conf", "rb");
			if (f) {
				size_t len;
				if (fread(&len, sizeof(len), 1, f) == 1) {
					username.resize(len);
					fread(username.data(), 1, len, f);
				}

				fclose(f);
			}
			if (testMode == EnumTestMode::SERVER) {
				username = "ServerTest";
			} else if (testMode == EnumTestMode::CLIENT) {
				username = "ClientTest";
			}
			LOG::Print("Username is now: %s", username.data());

			// Determine the time when the game booted up
			auto duration = std::chrono::system_clock::now().time_since_epoch();
			bootTime = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

			// If we are testing a server, create it and instantly connect to it!
			if (testMode == EnumTestMode::SERVER) {
				StartServer();
			}
			if (testMode != EnumTestMode::NONE) {
				ConnectionDetails details = {
					.hostname = "127.0.0.1",
					.port = DEFAULT_SERVER_PORT
				};
				ConnectToServer(details);
			}
		}

		void StartSearch() {
			if (!SetState(NetworkState::NONE, NetworkState::SEARCHING)) {
				LOG::Print("Cannot start searching for connections while already connected");
				return;
			}
			p2p = CreateP2P();
		}

		void ConnectToPeer() {
			if (!SetState(NetworkState::WAITING, NetworkState::HANDSHAKE)) {
				LOG::Print("Cannot connect without being in waiting state");
				return;
			}
			p2p->Connect();
		}

		void PollPackets() {
			if (client != nullptr) {
				client->Poll();
			}
			if (server != nullptr) {
				server->Poll();
			}
		}

		void StartServer() {
			if (server != nullptr) return;
			server = CreateServer();
		}

		void ConnectToServer(ConnectionDetails connection) {
			// Ensure we are in none or handshake when we try to connect to a server
			if (state == NetworkState::NONE) {
				SetState(NetworkState::NONE, NetworkState::PLAY);
			} else if (state == NetworkState::HANDSHAKE) {
				SetState(NetworkState::HANDSHAKE, NetworkState::PLAY);
			} else {
				LOG::Print("Cannot connect to server unless directly connecting or handshaking");
				return;
			}
			if (client == nullptr) {
				client = CreateClient();
			}
			client->Connect(connection.hostname, connection.port);
		}
	};
};