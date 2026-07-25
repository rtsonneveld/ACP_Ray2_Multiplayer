#include "peer.h"
#include "../../util/clipboard.h"
#include "../../util/base64.h"

void on_state_changed(juice_agent_t* agent, juice_state_t state, void* user_ptr) {
	LOG_Print("State: %s", juice_state_to_string(state));
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
	char buffer[256];
	if (size > 255)
		size = 255;
	memcpy(buffer, data, size);
	buffer[size] = '\0';
	LOG_Print("Received %s", buffer);
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
	std::string sdp = base64_decode(ReadClipboard());
	juice_set_remote_description(agent, sdp.c_str());

	// TODO Look at continuing from here
}

bool P2PConnection::isSuccessful() {
	return juice_get_state(agent) == JUICE_STATE_COMPLETED;
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