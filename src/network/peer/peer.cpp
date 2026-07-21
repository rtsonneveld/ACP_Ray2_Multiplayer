#include "peer.h"

void P2PConnection::initialize() {
	juice_set_log_level(JUICE_LOG_LEVEL_DEBUG);
	
	// Configure using publicly available STUN server
	juice_config_t config;
	memset(&config, 0, sizeof(config));
	config.stun_server_host = "stun.l.google.com";
	config.stun_server_port = 19302;
	config.user_ptr = NULL;

	// TODO Send mesages over juice to establish the handshake and determine a host
	// based on which side is older
	// https://github.com/paullouisageneau/libjuice/blob/master/test/connectivity.c

	// Create the agent
	agent = juice_create(&config);
	if (!agent) {
		LOG_Print("Failed to create libjuice agent");
		exit(EXIT_FAILURE);
	}

	// Start the gathering process
	juice_gather_candidates(agent);
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

	// Destroy the agent
	juice_destroy(agent);

	// Wait so the OS has time to destroyt he socket
	std::this_thread::sleep_for(std::chrono::milliseconds(50));

	// Return the established connection we set earlier in on_gathering_done
	return conn;
}

std::unique_ptr<P2PConnection> createP2P() {
	auto connection = std::make_unique<P2PConnection>();
	connection->initialize();
	return connection;
}