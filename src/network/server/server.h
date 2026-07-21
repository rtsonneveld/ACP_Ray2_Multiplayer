#pragma once

#include "../network.h"

/** The logical server run by the current host. Server relays information and holds minimal state. */
class RaymanServer {
private:
	ENetHost* server;
	std::thread thread;
	std::atomic<bool> running {false};

	/** Resets the connection. */
	void reset();

public:
	/** Initializes the server with the given address. */
	void initialize(ENetAddress address);

	/** Ticks the server thread. */
	void tick();

	/** Broadcasts the given packet. */
	void broadcast(Packet packet);

	/** Sends the given packet to the given player. */
	void send(int playerId, Packet packet);

	/** Shuts down the server. */
	void shutdown();
};

/** Creates a new host server. */
std::unique_ptr<RaymanServer> createServer();