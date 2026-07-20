#pragma once

#include "../network.h"

#define RAYMAN_SERVER_PORT 53123

class RaymanServer {
private:
	ENetHost* server;
	std::thread thread;
	std::atomic<bool> running {false};

public:
	/** Initializes the server with the given address. */
	void initialize(ENetAddress address);

	/** Ticks the server thread. */
	void tick();

	/** Shuts down the server. */
	void shutdown();
};

/** Creates a new host server. */
std::unique_ptr<RaymanServer> createServer();