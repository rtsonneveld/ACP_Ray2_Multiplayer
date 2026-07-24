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

bool NTW_SetState(NetworkState from, NetworkState to) {
	if (state != from) return false;
	state = to;
	return true;
}

void NTW_Initialize() {
	if (enet_initialize() != 0) {
		fprintf(stderr, "An error occurred while initializing ENet.\n");
		exit(EXIT_FAILURE);
	}
	atexit(enet_deinitialize);
}

void NTW_StartSearch() {
	if (!NTW_SetState(NetworkState::NONE, NetworkState::SEARCHING)) {
		LOG_Print("Cannot start searching for connections while already connected");
		return;
	}
	p2p = createP2P();
}

void NTW_ConnectToPeer() {
	if (!NTW_SetState(NetworkState::WAITING, NetworkState::HANDSHAKE)) {
		LOG_Print("Cannot connect without being in waiting state");
		return;
	}
	p2p->connect();
}

void NTW_test() {
	// Create the client
	client = createClient();

	// Create a server instance to test
	server = createServer();

	// Attempt to connect to the server
	client->connect("127.0.0.1", DEFAULT_SERVER_PORT);
}