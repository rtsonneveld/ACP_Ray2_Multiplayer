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
		LOG_Print("An error occurred while trying to create an ENet server host.");
		exit(EXIT_FAILURE);
	}

	// Create a thread to poll the server for updates
	running = true;
	thread = std::thread(&RaymanServer::tick, this);
	thread.detach();
	LOG_Print("Started new ENet server");
}

void RaymanServer::tick() {
	// Tick for events for at most 50ms before re-checking if the thread has been asked to stop
	ENetEvent event;
	while (running) {
		if (enet_host_service(server, &event, 50) > 0) {
			switch (event.type) {
			case ENET_EVENT_TYPE_CONNECT:
				char ip[64];
				enet_address_get_host_ip(&event.peer->address, ip, sizeof(ip));
				LOG_Print("Received new connection from %s:%d", ip, event.peer->address.port);
				// TODO Track clients and identify them with player id
				break;
			case ENET_EVENT_TYPE_RECEIVE:
				LOG_Print("[server] Received packet of length %u from %s:%d", event.packet->dataLength, event.peer->address.host, event.peer->address.port);
				enet_packet_destroy(event.packet);
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				LOG_Print("Received disconnect request from %s:%d", event.peer->address.host, event.peer->address.port);
				break;
			}
		}
	}
}

void RaymanServer::shutdown() {
	// Destroy the ENet server
	running = false;
	enet_host_destroy(server);
}

void RaymanServer::broadcast(Packet packet) {
	ENetPacket* enetPacket = enet_packet_create("packet", strlen("packet") + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_host_broadcast(server, 0, enetPacket);
}

void RaymanServer::send(int playerId, Packet packet) {
	ENetPacket* enetPacket = enet_packet_create("packet", strlen("packet") + 1, ENET_PACKET_FLAG_RELIABLE);
	ENetPeer* peer;
	// TODO Identify which peer based on the player id
	enet_peer_send(peer, 0, enetPacket);
}

std::unique_ptr<RaymanServer> createServer() {
	// Determine the address to host on, we always host on the same port on localhost.
	auto raymanServer = std::make_unique<RaymanServer>();
	ENetAddress address;
	address.host = ENET_HOST_ANY;
	address.port = DEFAULT_SERVER_PORT;
	raymanServer->initialize(address);
	return raymanServer;
}