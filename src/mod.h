#pragma once

#include "network/network.h"
#include <ACP_Ray2.h>

namespace R2MP {
	/** Janky patch to allow multiple instances of Rayman2.exe to run simultaniously. */
	void MOD_PatchMutex();

	/** Main entry point for engine ticks. */
	void MOD_EngineTick();

	/** Registers custom commands for R2Console. */
	void MOD_RegisterCommands();

	/** Main entry point for displaying stuff. */
	void MOD_fn_vDisplayAll();

}