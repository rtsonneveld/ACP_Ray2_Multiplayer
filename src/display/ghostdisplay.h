#pragma once
#include "texturemanager.h"
#include "../constants.h"

namespace R2MP::DSP {
	
	struct BoneDisplayInfo {
		float sizeX;
		float sizeY;
		float offsetZ;
	};

	class GhostDisplay {
	private:
		GLI_tdstMaterial materials[Constants::GHOST_NUMBONES];
		static constexpr BoneDisplayInfo boneDisplayInfo[Constants::GHOST_NUMBONES] = {
			{.sizeX = 1.2f, .sizeY = 1.2f, .offsetZ = 0.0f}, // Body
			{.sizeX = 0.8f, .sizeY = 0.8f, .offsetZ = 0.0f }, // Right hand
			{.sizeX = 1.0f, .sizeY = 1.0f, .offsetZ = 0.0f }, // Left hand
			{.sizeX = 1.0f, .sizeY = 1.0f, .offsetZ = 0.0f }, // Right foot
			{.sizeX = 1.0f, .sizeY = 1.0f, .offsetZ = 0.0f }, // Left foot
			{.sizeX = 1.1f, .sizeY = 1.1f, .offsetZ = 0.4f }, // Head
		};
	public:
		void Init();
		void DrawGhosts();
	};
}