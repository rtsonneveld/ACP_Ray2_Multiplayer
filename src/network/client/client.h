#pragma once

#include "../network.h"

class RaymanClient {
private:
	ENetHost* client;

public:
	/** Initializes the client. */
	void initialize();

	/** Shuts down the client. */
	void shutdown();
};

/** Creates a new client. */
RaymanClient createClient();