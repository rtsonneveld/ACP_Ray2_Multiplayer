#include "peer.h"
#include "../packet/handshake_packets.h"
#include "../../util/clipboard.h"
#include "../../util/base64.h"

void on_state_changed(juice_agent_t* agent, juice_state_t state, void* user_ptr) {
	if (state == JUICE_STATE_COMPLETED) {
		// Connection is completely between both sides!
		NTW_SetState(NetworkState::WAITING, NetworkState::HANDSHAKE);

		// Send the introduction packet with player information
		P2PConnection* p2p = (P2PConnection*)user_ptr;
		HandshakeIntroductionPacket packet{
			.username = NTW_GetUsername(),
			.bootTime = NTW_GetBootTime(),
			.isServer = NTW_IsRunningServer()
		};
		p2p->send(packet);
	} else if (state == JUICE_STATE_FAILED) {
		LOG_Print("Failed to create connection to peer, please try again!");
		NTW_ResetState();
	}
}

void on_gathering_done(juice_agent_t* agent, void* user_ptr) {
	char sdp[JUICE_MAX_SDP_STRING_LEN];
	auto result = juice_get_local_description(agent, sdp, sizeof(sdp));
	if (result < 0) {
		LOG_Print("Failed to find peers!");
		return;
	}
	SetClipboard(base64_encode(sdp, strlen(sdp)));
	LOG_Print("Copied information to clipboard, send this to peer!");
	NTW_SetState(NetworkState::SEARCHING, NetworkState::WAITING);
}

void on_receive(juice_agent_t* agent, const char* data, size_t size, void* user_ptr) {
	const auto* bytes = reinterpret_cast<const uint8_t*>(data);
	auto decoder = NTW_DecodePacket(bytes, size);
	P2PConnection* p2p = (P2PConnection*)user_ptr;
	p2p->handle(decoder);
}

void P2PConnection::handle(DecodedPacket& decoder) {
	switch (decoder.id()) {
	case 0: {
		auto packet = decoder.get<HandshakeIntroductionPacket>();

		// If both users have the same username, the connection cannot proceed!
		if (NTW_GetUsername() == packet.username) {
			LOG_Print("Cannot form connection between users with the same username");
			destroy();
			return;
		}

		// Check that, if we are the server, this username is available
		if (NTW_IsRunningServer() && NTW_GetUsername() == packet.username) { // TODO Use proper check here when we have server-side player state!
			LOG_Print("Cannot form connection between users as username is taken");
			destroy();
			return;
		}

		// Determine deterministically who the host will be
		auto host = NTW_GetUsername();
		if (packet.isServer) {
			// Other player is a server, they are the host!
			packet.username;
		} else if (NTW_IsRunningServer()) {
			// We are the host!
		} else if (packet.bootTime < NTW_GetBootTime()) {
			// Other player booted earlier, they are the host!
			host = packet.username;
		} else if (packet.bootTime == NTW_GetBootTime() && packet.username.compare(NTW_GetUsername()) < 0) {
			// We somehow tied for boot time but they are alphabetically
			host = packet.username;
		}
		HandshakeRequestTransferPacket confirmPacket{
			.host = host
		};
		send(confirmPacket);
		return;
	}
	case 1: {
		// When we've confirmed the transfer, if necessary start the server and hand over the connection to ENet.
		auto packet = decoder.get<HandshakeRequestTransferPacket>();
		if (packet.host == NTW_GetUsername()) {
			// On the host side, create the server and connect to it immediately.
			NTW_StartServer();
			ConnectionDetails details = {
				.hostname = "127.0.0.1",
				.port = DEFAULT_SERVER_PORT
			};
			NTW_Connect(details);
		} else {
			// TODO Start up a connection like client-server over the peer connection with some reliability library
		}
		return;
	}
	}
}

void P2PConnection::initialize() {
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
		LOG_Print("Failed to create libjuice agent");
		exit(EXIT_FAILURE);
	}

	// Start the gathering process
	juice_gather_candidates(agent);
}

void P2PConnection::connect() {
	// Fill the other side's connection and wait for the handshake to be complete
	std::string sdp = base64_decode(ReadClipboard());
	juice_set_remote_description(agent, sdp.c_str());
}

bool P2PConnection::isSuccessful() {
	return juice_get_state(agent) == JUICE_STATE_COMPLETED;
}

template<typename T>
void P2PConnection::send(const T& packet) {
	if (!isSuccessful()) {
		LOG_Print("Cannot send packet while not fully connected to peer");
		return;
	}
	auto encoded = NTW_EncodePacket(packet);
	juice_send(agent, reinterpret_cast<const char*>(encoded.get()), encoded.length());
}

void P2PConnection::destroy() {
	// Destroy the agent
	juice_destroy(agent);

	// Wait so the OS has time to destroy the socket
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

std::unique_ptr<P2PConnection> createP2P() {
	auto connection = std::make_unique<P2PConnection>();
	connection->initialize();
	return connection;
}