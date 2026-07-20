#include "client.h"

void RaymanClient::initialize() {
	client = enet_host_create(
		NULL, // NULL creates a client
		1, // Allow one connection
		2, // Use 2 channels
		0, // Do not limit bandwidth
		0
	);
	if (client == NULL) {
		fprintf(stderr, "An error occurred while trying to create an ENet client.\n");
		exit(EXIT_FAILURE);
	}
}

void RaymanClient::shutdown() {
	enet_host_destroy(client);
}

RaymanClient createClient() {
	auto raymanClient = RaymanClient();
	raymanClient.initialize();
	return raymanClient;
}