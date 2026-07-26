#include "bonetools.h"
namespace R2MP {

	static int BoneToChannelIndex(int index) {
		// Channel names taken from rayman.CHL
		static const int table[Constants::GHOST_NUMBONES] = {
		  0, // corps: Body
		  2, // main_d: Right hand
		  3, // Main_G: Left hand
		  6, // pied_d: Right foot
		  7, // pied_g: Left foot
		  8 // TETE_BASE: Head
		};
		if (index < 0 || index >= 7) return -1;
		return table[index];
	}

	ByteVec3* GetBonePositions()
	{
		ByteVec3 bonePositions[Constants::GHOST_NUMBONES];
		for (int i = 0;i < Constants::GHOST_NUMBONES;i++) {

		}
		return bonePositions;
	}
}