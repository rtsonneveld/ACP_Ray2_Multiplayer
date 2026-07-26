#pragma once

#define DEFAULT_SERVER_PORT 53123

#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#include <cstdio>
#include <iostream>
#include <thread>
#include <chrono>
#include <juice/juice.h>
#include <enet/enet.h>

#include "packet/registry.h"
#include "../util/logging.h"

namespace R2MP {
	namespace NET {
		/** Stores details on a connection with hostname and port. */
		struct ConnectionDetails {
			std::string hostname;
			int port;
		};

		/** The different states of a networking connection of an instance. */
		enum class NetworkState {
			NONE,
			SEARCHING,
			WAITING,
			HANDSHAKE,
			PLAY
		};

		/** The diffenent testing modes set up through command arguments. */
		enum class EnumTestMode {
			NONE = 0,
			SERVER,
			CLIENT
		};

		/** Provides networking to another side. */
		class NetworkConnection {
		public:
			/** Sends an encoded packet through this connection. */
			virtual void SendEncoded(EncodedPacket& packet) = 0;

			/** Sends a packet through this connection. */
			template<typename T>
			void Send(const T& packet) {
				auto encoded = EncodePacket(packet);
				SendEncoded(encoded);
			}
		};

		/** Returns the current serverbound connection, if one exists. */
		NetworkConnection* GetServerboundConnection();

		/** Sets the current serverbound networking to the given implementation. */
		void SetServerboundConnection(NetworkConnection* networking);

		/** Creates a new player off the given connection. */
		uint32_t CreatePlayer(NetworkConnection* networking);

		/** Removes a player that has disconnected. */
		void RemovePlayer(uint32_t playerId);

		/** Returns the unique id of this client session. */
		uint32_t GetClientId();

		/** Returns the time when this instance booted up. */
		long long GetBootTime();

		/** Returns the username of the client. */
		std::string GetUsername();

		/** Sets the username of the client. */
		void SetUsername(std::string username);

		/** Initializes multiplayer connectivity. */
		void Initialize(EnumTestMode testMode = EnumTestMode::NONE);

		/** Returns the current networking state. */
		NetworkState GetState();

		/** Resets the networking state. */
		void ResetState();

		/** Updates the current networking state. */
		bool SetState(NetworkState from, NetworkState to);

		/** Whether this client is running a server. */
		bool IsRunningServer();

		/** Starts searching for STUN connections. */
		void StartSearch();

		/** Connects to the peer given the current SDP in the clipboard. */
		void ConnectToPeer();

		/** Runs any queued packets on the engine thread. */
		void PollPackets();

		/** Starts running a server. */
		void StartServer();

		/** Connects the client across the given connection. */
		void ConnectToServer(ConnectionDetails connection);

		/** Handles a play clientbound packet. */
		void HandlePlayClientbound(DecodedPacket& packet);

		/** Handles a play serverbound packet. */
		void HandlePlayServerbound(uint32_t playerId, DecodedPacket& packet);
	};
};