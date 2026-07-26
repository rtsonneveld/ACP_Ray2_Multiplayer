#pragma once

#include "../network.h"

namespace R2MP {
	namespace NET {
		/** The logical server run by the current host. Server relays information and holds minimal state. */
		class RaymanServer {
		private:
			ENetHost* server;
			std::queue<DecodedPacket> packetQueue;
			std::mutex queueMutex;
			std::thread thread;
			std::atomic<bool> running{ false };

			/** Resets the connection. */
			void Reset();

		public:
			/** Initializes the server with the given address. */
			void Initialize(ENetAddress address);

			/** Ticks the server thread. */
			void Tick();

			/** Broadcasts the given packet. */
			template<typename T>
			void Broadcast(EncodedPacket& packet);

			/** Sends the given packet to the given peer. */
			void Send(ENetPeer* peer, EncodedPacket& packet);

			/** Shuts down the server. */
			void Shutdown();

			/** Runs pending packets on the engine thread. */
			void Poll();
		};

		/** Creates a new host server. */
		std::unique_ptr<RaymanServer> CreateServer();
	};
};