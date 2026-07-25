#pragma once

#include "network/network.h"
#include <ACP_Ray2.h>

namespace R2MP {

	/** Main entry point for engine ticks. */
	void MOD_EngineTick();

	/** Registers custom commands for R2Console. */
	void MOD_RegisterCommands();

	/** Main entry point for displaying stuff. */
	void MOD_fn_vDisplayAll();

}