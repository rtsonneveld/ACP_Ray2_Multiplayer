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

#include "packet/packet.h"
#include "../util/logging.h"

int NTW_test();