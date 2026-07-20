#include "server.h"

void RaymanServer::initialize(ENetAddress address) {
	// Create the server host itself
	server = enet_host_create(
		&address,
		64, // Allow up to 64 clients to be connected
		2, // Use 2 channels
		0, // Do not limit bandwidth
		0
	);
	if (server == NULL) {
		fprintf(stderr, "An error occurred while trying to create an ENet server host.\n");
		exit(EXIT_FAILURE);
	}

	// Create a thread to poll the server for updates
	running = true;
	thread = std::thread(&RaymanServer::tick, this);
}

void RaymanServer::tick() {
	// Tick for events for at most 50ms before re-checking if the thread has been asked to stop
	ENetEvent event;
	while (running && enet_host_service(server, &event, 50) > 0) {
		switch (event.type) {
		case ENET_EVENT_TYPE_CONNECT:
			break;
		case ENET_EVENT_TYPE_RECEIVE:
			break;
		case ENET_EVENT_TYPE_DISCONNECT:
			break;
		}
	}
}

void RaymanServer::shutdown() {
	// Shut down the tick thread
	running = false;
	if (thread.joinable()) {
		thread.join();
	}

	// Destroy the ENet server
	enet_host_destroy(server);
}

std::unique_ptr<RaymanServer> createServer() {
	// Determine the address to host on, we always host on the same port on localhost.
	auto raymanServer = std::make_unique<RaymanServer>();
	ENetAddress address;
	address.host = ENET_HOST_ANY;
	address.port = RAYMAN_SERVER_PORT;
	raymanServer->initialize(address);
	return raymanServer;
}