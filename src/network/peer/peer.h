#pragma once

#include "../network.h"

/** Stores details on a connection established through peer-2-peer. */
struct EstablishedConnection {
	std::string hostname;
	int port;
};

/** Stores details for a single P2P connection. */
class P2PConnection {
private:
	juice_agent_t* agent;

public:
	/** Initializes this connection. */
	void initialize();

	/** Returns whether the connection was successfully made. */
	bool isSuccessful();

	/** Hands over this connection to ENet. */
	EstablishedConnection handover();
};

/** Starts the process of finding peers. */
std::unique_ptr<P2PConnection> createP2P();