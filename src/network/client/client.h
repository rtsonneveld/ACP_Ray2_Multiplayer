#pragma once

#include "../network.h"

/** An ENet client which connects to the server. Even the hosts runs a local client. */
class RaymanClient {
private:
	ENetHost* client;
	ENetPeer* peer;
	bool connected;
	std::thread thread;
	std::atomic<long> awaitDisconnect{ 0 };
	std::atomic<bool> awaitConnect{ false };
	std::atomic<bool> running{ false };

	/** Resets the connection. */
	void reset();

public:
	/** Returns whether this client is connected. */
	bool isConnected();

	/** Initializes the client. */
	void initialize();

	/** Ticks the client thread. */
	void tick();

	/** Shuts down the client. */
	void shutdown();

	/** Sends a packet to the server. */
	void send(Packet packet);

	/** Connects to a server at the given hostname and port. */
	void connect(std::string hostname, int port);
	
	/** Disconnects from the server. */
	void disconnect();
};

/** Creates a new client. */
std::unique_ptr<RaymanClient> createClient();