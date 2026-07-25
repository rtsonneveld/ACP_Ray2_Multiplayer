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
	switch (decoder.id()) {
	case 0: {
		auto packet = decoder.get<HandshakeIntroductionPacket>();
		LOG_Print("[peer] Received introduction packet from %s!", packet.username.data());
		break;
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

EstablishedConnection P2PConnection::handover() {
	// Ensure the connection is successfull and we have a valid connection
	if (!isSuccessful()) {
		LOG_Print("Tried to hand over incomplete P2P connection");
		exit(EXIT_FAILURE);
	}

	// Extract the connection made
	char local[JUICE_MAX_ADDRESS_STRING_LEN];
	char remote[JUICE_MAX_ADDRESS_STRING_LEN];
	juice_get_selected_candidates(agent, local, sizeof(local), remote, sizeof(remote));
	EstablishedConnection conn;
	std::istringstream ss(remote);
	std::string token;
	ss >> token;
	ss >> token;
	ss >> token;
	ss >> token;
	ss >> conn.hostname;
	ss >> conn.port;
	LOG_Print("Found connection over %s:%d", conn.hostname.c_str(), conn.port);
	destroy();
	return conn;
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