#include "network.h"
#include "client/client.h"
#include "server/server.h"

std::unique_ptr<RaymanClient> client;
std::unique_ptr<RaymanServer> server;

int NTW_test() {
	// Initialize ENet
	if (enet_initialize() != 0) {
		fprintf(stderr, "An error occurred while initializing ENet.\n");
		return EXIT_FAILURE;
	}
	atexit(enet_deinitialize);

	// Create the client
	client = createClient();

	// Create a server instance to test
	server = createServer();

	// Attempt to connect to the server
	client->connect("127.0.0.1", DEFAULT_SERVER_PORT);
}