#pragma once

#include "network/network.h"
#include <ACP_Ray2.h>

/** Main entry point for engine ticks. */
void MOD_EngineTick();

/** Registers custom commands for R2Console. */
void MOD_RegisterCommands();