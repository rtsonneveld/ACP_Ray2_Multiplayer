#include "peer.h"
#include "../packet/handshake_packets.h"
#include "../../util/clipboard.h"
#include "../../util/base64.h"

namespace R2MP {
	namespace NET {
		/** Implements a serverbound networking solution with P2P through libjuice. */
		class JuiceServerboundNetworking : public NetworkConnection {
		public:
			P2PConnection* p2p;

			void SendImpl(EncodedPacket& packet) {
				p2p->Send(packet);
			}
		};

		void on_state_changed(juice_agent_t* agent, juice_state_t state, void* user_ptr) {
			if (state == JUICE_STATE_COMPLETED) {
				// Connection is completely between both sides!
				SetState(NetworkState::WAITING, NetworkState::HANDSHAKE);

				// Send the introduction packet with player information
				P2PConnection* p2p = (P2PConnection*)user_ptr;
				HandshakeIntroductionPacket packet{
					.username = GetUsername(),
					.bootTime = GetBootTime(),
					.isServer = IsRunningServer()
				};
				p2p->Send(packet);
			} else if (state == JUICE_STATE_FAILED) {
				LOG::Print("Failed to create connection to peer, please try again!");
				ResetState();
			}
		}

		void on_gathering_done(juice_agent_t* agent, void* user_ptr) {
			char sdp[JUICE_MAX_SDP_STRING_LEN];
			auto result = juice_get_local_description(agent, sdp, sizeof(sdp));
			if (result < 0) {
				LOG::Print("Failed to find peers!");
				return;
			}
			SetClipboard(Base64Encode(sdp, strlen(sdp)));
			LOG::Print("Copied information to clipboard, send this to peer!");
			SetState(NetworkState::SEARCHING, NetworkState::WAITING);
		}

		void on_receive(juice_agent_t* agent, const char* data, size_t size, void* user_ptr) {
			const auto* bytes = reinterpret_cast<const uint8_t*>(data);
			auto decoder = DecodePacket(bytes, size, 0);
			P2PConnection* p2p = (P2PConnection*)user_ptr;

			if (p2p->InPlayPhase()) {
				if (IsRunningServer()) {
					HandlePlayServerbound(p2p->GetPlayerId(), decoder);
				} else {
					HandlePlayClientbound(decoder);
				}
			} else {
				p2p->Handle(decoder);
			}
		}

		void P2PConnection::Handle(DecodedPacket& decoder) {
			switch (decoder.Id()) {
			case 0: {
				auto packet = decoder.Get<HandshakeIntroductionPacket>();

				// If both users have the same username, the connection cannot proceed!
				if (GetUsername() == packet.username) {
					LOG::Print("Cannot form connection between users with the same username");
					Destroy();
					return;
				}

				// Check that, if we are the server, this username is available
				if (IsRunningServer() && GetUsername() == packet.username) { // TODO Use proper check here when we have server-side player state!
					LOG::Print("Cannot form connection between users as username is taken");
					Destroy();
					return;
				}

				// If both users are hosts, we can't connect them!
				if (IsRunningServer() && packet.isServer) {
					LOG::Print("Cannot form connection between two players already acting as hosts");
					return;
				}

				// Determine deterministically who the host will be
				auto host = GetUsername();
				if (packet.isServer) {
					// Other player is a server, they are the host!
					packet.username;
				} else if (IsRunningServer()) {
					// We are the host!
				} else if (packet.bootTime < GetBootTime()) {
					// Other player booted earlier, they are the host!
					host = packet.username;
				} else if (packet.bootTime == GetBootTime() && packet.username.compare(GetUsername()) < 0) {
					// We somehow tied for boot time but they are alphabetically
					host = packet.username;
				}
				HandshakeCompletePacket confirmPacket{
					.host = host
				};
				Send(confirmPacket);
				return;
			}
			case 1: {
				// When we've confirmed the P2P connection, change to the play protocol and boot up the server as a host.
				auto packet = decoder.Get<HandshakeCompletePacket>();

				// Create the new networking implementation over this channel
				JuiceServerboundNetworking networking;
				networking.p2p = this;
				play = true;

				if (packet.host == GetUsername()) {
					// On the host side, create the server and connect to it immediately locally.
					if (!IsRunningServer()) {
						StartServer();
						ConnectionDetails details = {
							.hostname = "127.0.0.1",
							.port = DEFAULT_SERVER_PORT
						};
						ConnectToServer(details);
					}

					// Submit this connection as a new player connection
					playerId = CreatePlayer(&networking);
				} else {
					// On the client side treat the other side as a host
					SetServerboundConnection(&networking);
				}
				return;
			}
			}
		}

		void P2PConnection::Initialize() {
			juice_set_log_level(JUICE_LOG_LEVEL_DEBUG);

			// Configure using publicly available STUN server
			juice_config_t config;
			memset(&config, 0, sizeof(config));
			config.stun_server_host = "stun.l.google.com";
			config.stun_server_port = 19302;
			config.user_ptr = this;
			config.cb_state_changed = on_state_changed;
			config.cb_gathering_done = on_gathering_done;
			config.cb_recv = on_receive;

			// Create the agent
			agent = juice_create(&config);
			if (!agent) {
				LOG::Print("Failed to create libjuice agent");
				exit(EXIT_FAILURE);
			}

			// Start the gathering process
			juice_gather_candidates(agent);
		}

		void P2PConnection::Connect() {
			// Fill the other side's connection and wait for the handshake to be complete
			std::string sdp = Base64Decode(ReadClipboard());
			juice_set_remote_description(agent, sdp.c_str());
		}

		bool P2PConnection::IsSuccessful() {
			return juice_get_state(agent) == JUICE_STATE_COMPLETED;
		}

		template<typename T>
		void P2PConnection::Send(const T& packet) {
			auto encoded = EncodePacket(packet);
			Send(encoded);
		}

		void P2PConnection::Send(EncodedPacket& encoded) {
			if (!IsSuccessful()) {
				LOG::Print("Cannot send packet while not fully connected to peer");
				return;
			}
			juice_send(agent, reinterpret_cast<const char*>(encoded.Get()), encoded.Length());
		}

		void P2PConnection::Destroy() {
			juice_destroy(agent);
			if (play && IsRunningServer()) {
				RemovePlayer(playerId);
			}
		}

		bool P2PConnection::InPlayPhase() {
			return play;
		}

		uint32_t P2PConnection::GetPlayerId() {
			return playerId;
		}

		std::unique_ptr<P2PConnection> CreateP2P() {
			auto connection = std::make_unique<P2PConnection>();
			connection->Initialize();
			return connection;
		}
	};
};