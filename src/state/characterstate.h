#pragma once
#include <ACP_Ray2.h>

#define MP_GHOSTBONES 6

namespace R2MP {

	struct GhostBonePositions {
		MTH3D_tdstVector ghostBones[MP_GHOSTBONES];
	};

	struct CharacterState {
		MTH3D_tdstVector position;
		GhostBonePositions ghostBonePositions;
	};

}