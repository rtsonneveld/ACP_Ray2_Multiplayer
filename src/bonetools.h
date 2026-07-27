#pragma once
#include "util/vector.h"
#include "constants.h"
#include <array>
#include <vector>

#include <ACP_Ray2.h>


namespace R2MP {
	std::array<ByteVec3, Constants::GHOST_NUMBONES> GetCompressedBonePositions(HIE_tdstSuperObject* boneSource);
	HIE_tdstSuperObject* DetermineBoneSource();
	std::array<Vec3, Constants::GHOST_NUMBONES> DecompressBonePositions(std::array<ByteVec3, Constants::GHOST_NUMBONES> compressedBonePositions, MTH3D_tdstVector origin);
}