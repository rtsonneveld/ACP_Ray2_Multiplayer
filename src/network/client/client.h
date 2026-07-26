#pragma once

#include "../network.h"

namespace R2MP {
	namespace NET {
		/** An ENet client which connects to the server. Even the hosts runs a local client. */
		class RaymanClient {
		private:
			ENetHost* client;
			ENetPeer* peer;
			bool connected;
			std::queue<DecodedPacket> packetQueue;
			std::mutex queueMutex;
			std::thread thread;
			std::atomic<long> awaitDisconnect{ 0 };
			std::atomic<bool> awaitConnect{ false };
			std::atomic<bool> running{ false };

			/** Resets the connection. */
			void Reset();

		public:
			/** Returns whether this client is connected. */
			bool IsConnected();

			/** Initializes the client. */
			void Initialize();

			/** Ticks the client thread. */
			void Tick();

			/** Shuts down the client. */
			void Shutdown();

			/** Sends a packet to the server. */
			void Send(EncodedPacket& packet);

			/** Connects to a server at the given hostname and port. */
			void Connect(std::string hostname, int port);

			/** Disconnects from the server. */
			void Disconnect();

			/** Runs pending packets on the engine thread. */
			void Poll();
		};

		/** Creates a new client. */
		std::unique_ptr<RaymanClient> CreateClient();
	};
};