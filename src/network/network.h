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
#include <enet/enet.h>

#include "packet/packet.h"
#include "../util/logging.h"

int NTW_test();