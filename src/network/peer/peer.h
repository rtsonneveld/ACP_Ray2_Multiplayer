#pragma once

#include "../network.h"

namespace R2MP {
	namespace NET {
		/** Stores details for a single P2P connection. */
		class P2PConnection {
		private:
			juice_agent_t* agent;
			bool play = false;
			uint32_t playerId = 0;

		public:
			/** Initializes this connection. */
			void Initialize();

			/** Returns whether the connection was successfully made. */
			bool IsSuccessful();

			/** Whether this connection is in the play phase. */
			bool InPlayPhase();

			/** Returns the player id of this connected player, if applicable. */
			uint32_t GetPlayerId();

			/** Starts connecting using current information in clipboard. */
			void Connect();

			/** Destroys the connection. */
			void Destroy();

			/** Handles the given packet. */
			void Handle(DecodedPacket& packet);

			/** Sends a packet to the peer. */
			template<typename T>
			void Send(const T& packet) {
				auto encoded = EncodePacket(packet);
				Send(encoded);
			}

			/** Sends a packet to the peer. */
			void Send(EncodedPacket& packet);
		};

		/** Starts the process of finding peers. */
		std::unique_ptr<P2PConnection> CreateP2P();
	};
};