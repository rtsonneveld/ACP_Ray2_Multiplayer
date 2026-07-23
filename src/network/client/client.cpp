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
		LOG_Print("An error occurred while trying to create an ENet client.");
		exit(EXIT_FAILURE);
	}

	// Create a thread to poll the client for updates
	running = true;
	thread = std::thread(&RaymanClient::tick, this);
	thread.detach();
	LOG_Print("Started new ENet client");
}

void RaymanClient::shutdown() {
	if (connected) {
		enet_peer_disconnect(peer, 0);
		reset();
	}
	running = false;
	enet_host_destroy(client);
}

void RaymanClient::reset() {
	enet_peer_reset(peer);
	connected = false;
	awaitDisconnect = 0;
}

void RaymanClient::tick() {
	// Tick for events for at most 50ms before re-checking if the thread has been asked to stop
	ENetEvent event;
	while (running) {
		// Await connecting to the server
		if (awaitConnect) {
			awaitConnect = false;

			// Wait up to 5s to connect to the server
			if (enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
				connected = true;
				LOG_Print("Successfully connected to server");
			} else {
				LOG_Print("Failed to connect to server");
				continue;
			}
		}

		// Ignore while disconnected and sleep
		if (!connected) {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			continue;
		}

		// Force close connection if we've exceeded the connection time
		if (awaitDisconnect > 0) {
			auto duration = std::chrono::system_clock::now().time_since_epoch();
			auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
			if (milliseconds >= awaitDisconnect) {
				reset();
				continue;
			}
		}

		// Await a packet
		if (enet_host_service(client, &event, 50) > 0) {
			switch (event.type) {
			case ENET_EVENT_TYPE_RECEIVE:
				LOG_Print("[client] Received packet of length %u", event.packet->dataLength);
				enet_packet_destroy(event.packet);
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				LOG_Print("Successfully disconnected from server, data=%u", event.data);
				enet_peer_reset(peer);
				connected = false;
				break;
			}
		}
	}
}

void RaymanClient::connect(std::string hostname, int port) {
	// Don't connect if already connected
	if (connected) {
		LOG_Print("Client is already connected to a server");
		return;
	}

	// Determine the target address
	ENetAddress address;
	enet_address_set_host(&address, hostname.c_str());
	address.port = port;

	// Initiate the connection
	peer = enet_host_connect(client, &address, 2, 0);
	if (peer == NULL) {
		LOG_Print("An error occurred while trying to connect to the ENet server.");
		exit(EXIT_FAILURE);
	}
	awaitConnect = true;
}

void RaymanClient::disconnect() {
	if (!connected) return;

	// Gracefully tell the server we intend to disconnect
	LOG_Print("Informing server about disconnection");
	enet_peer_disconnect(peer, 0);

	// Store a time when we forcefully disconnect
	auto duration = std::chrono::system_clock::now().time_since_epoch();
	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
	awaitDisconnect = milliseconds + 3000;
}

template<typename T>
void RaymanClient::send(const T& packet) {
	if (!connected) {
		LOG_Print("Cannot send packet while not connected to server");
		return;
	}
	auto encoded = NTW_EncodePacket(packet);
	ENetPacket* enetPacket = enet_packet_create(encoded.get(), encoded.length, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, enetPacket);
}

bool RaymanClient::isConnected() {
	return connected;
}

std::unique_ptr<RaymanClient> createClient() {
	auto raymanClient = std::make_unique<RaymanClient>();
	raymanClient->initialize();
	return raymanClient;
}