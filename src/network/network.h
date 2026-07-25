#pragma once

/**
 * The networking solution works in two parts:
 * - ENet is used for a regular client-server architecture over UDP.
 * - libjuice is used for handshaking by creating a connection over STUN, once
 *	 the connection is succesfully established we create a new ENet connection
 *	 over the same port.
 */

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

enum class NetworkState {
	NONE,
	SEARCHING,
	WAITING,
	HANDSHAKE,
	PLAYER
};

enum class EnumTestMode {
	None = 0,
	Server,
	Client
};

/** Returns the unique id of this client session. */
uint32_t NTW_GetClientId();

/** Returns the time when this instance booted up. */
long long NTW_GetBootTime();

/** Returns the username of the client. */
std::string NTW_GetUsername();

/** Sets the username of the client. */
void NTW_SetUsername(std::string username);

/** Initializes multiplayer connectivity. */
void NTW_Initialize(EnumTestMode testMode = EnumTestMode::None);

/** Returns the current networking state. */
NetworkState NTW_GetState();

/** Resets the networking state. */
void NTW_ResetState();

/** Updates the current networking state. */
bool NTW_SetState(NetworkState from, NetworkState to);

/** Whether this client is running a server. */
bool NTW_IsRunningServer();

/** Starts searching for STUN connections. */
void NTW_StartSearch();

/** Connects to the peer given the current SDP in the clipboard. */
void NTW_ConnectToPeer();

/** Test function that optionally starts a server locally and creates a client */
static void NTW_test(EnumTestMode testMode);