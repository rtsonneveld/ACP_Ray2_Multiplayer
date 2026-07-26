#pragma once
#include "../constants.h"
#include <ACP_Ray2.h>

namespace R2MP {

	struct GhostBonePositions {
		MTH3D_tdstVector ghostBones[Constants::GHOST_NUMBONES];
	};

	struct CharacterState {
		MTH3D_tdstVector position;
		GhostBonePositions ghostBonePositions;
	};

}