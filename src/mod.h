#pragma once

#include "network/network.h"

namespace R2MP {
	/** Janky patch to allow multiple instances of Rayman2.exe to run simultaniously. */
	void PatchMutex();

	/** Main entry point for engine ticks. */
	void EngineTick();

	/** Registers custom commands for R2Console. */
	void RegisterCommands();

	/** Main entry point for displaying stuff. */
	void DisplayAll();

	/** Used to add newly loaded textures */
	void ComputeTextures();

}