#pragma once

#include "../network.h"

/** Stores details for a single P2P connection. */
class P2PConnection {
private:
	juice_agent_t* agent;

public:
	/** Initializes this connection. */
	void initialize();

	/** Returns whether the connection was successfully made. */
	bool isSuccessful();

	/** Starts connecting using current information in clipboard. */
	void connect();

	/** Hands over this connection to ENet. */
	ConnectionDetails handover();

	/** Destroys the connection. */
	void destroy();
	
	/** Handles the given packet. */
	void handle(DecodedPacket& packet);

	/** Sends a packet to the peer. */
	template<typename T>
	void send(const T& packet);
};

/** Starts the process of finding peers. */
std::unique_ptr<P2PConnection> createP2P();