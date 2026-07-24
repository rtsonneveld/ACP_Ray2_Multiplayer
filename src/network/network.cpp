#include "network.h"
#include "client/client.h"
#include "server/server.h"
#include "peer/peer.h"

std::unique_ptr<P2PConnection> p2p;
std::unique_ptr<RaymanClient> client;
std::unique_ptr<RaymanServer> server;
NetworkState state = NetworkState::NONE;

NetworkState NTW_GetState() {
	return state;
}

void NTW_Initialize() {
	if (enet_initialize() != 0) {
		fprintf(stderr, "An error occurred while initializing ENet.\n");
		exit(EXIT_FAILURE);
	}
	atexit(enet_deinitialize);
}

void NTW_StartSearch() {
	if (state != NetworkState::NONE) {
		LOG_Print("Cannot start searching for connections while already connected");
		return;
	}

	state = NetworkState::SEARCHING;
	p2p = createP2P();
}

void NTW_test() {
	// Create the client
	client = createClient();

	// Create a server instance to test
	server = createServer();

	// Attempt to connect to the server
	client->connect("127.0.0.1", DEFAULT_SERVER_PORT);
}