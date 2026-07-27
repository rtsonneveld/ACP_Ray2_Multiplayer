#include "bonetools.h"

#include <ACP_Ray2.h>

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

	ByteVec3 BonePosToByteVec3(MTH3D_tdstVector bonePos, MTH3D_tdstVector origin) {
		MTH3D_tdstVector relativePos;
		MTH3D_M_vSubVector(&relativePos, &bonePos, &origin);

		return Vec3ToByteVec3(relativePos, Constants::GHOST_MAXBONEDIST);
	}

	Vec3 ByteVec3ToBonePos(ByteVec3 relativePos, MTH3D_tdstVector origin) {

		Vec3 result = ByteVec3ToVec3(relativePos, Constants::GHOST_MAXBONEDIST);
		return Vec3(origin.x + result.x, origin.y + result.y, origin.z + result.z);
	}

	HIE_tdstSuperObject* DetermineBoneSource() {

		HIE_tdstSuperObject* mainActor = GAM_g_stEngineStructure->g_hMainActor;

		// Rayman
		if (strcmp(HIE_fn_szGetObjectFamilyName(mainActor), "rayman") == 0) {
			return mainActor;
		}

		// Hall of doors Raymond
		if (strcmp(GAM_g_stEngineStructure->szLevelName, "Mapmonde") == 0) {
			return HIE_fn_p_stFindObjectByName("YAM_RayMonde");
		}

		// Rayman skiing
		if (strcmp(HIE_fn_szGetObjectFamilyName(mainActor), "Rayman_ski") == 0) {
			return mainActor;
		}

		// Walking shell
		if (strcmp(HIE_fn_szGetObjectFamilyName(mainActor), "obus") == 0) {
			return mainActor;
		}

		// Otherwise
		return mainActor;
	}

	std::array<ByteVec3, Constants::GHOST_NUMBONES> GetCompressedBonePositions(HIE_tdstSuperObject* boneSource)
	{
		std::array<ByteVec3, Constants::GHOST_NUMBONES> bonePositions = {};

		if (boneSource == nullptr) {
			return bonePositions;
		}

		if (boneSource->hLinkedObject.p_stActor == nullptr) {
			return bonePositions;
		}

		GAM_tdst3dData* r3dData = boneSource->hLinkedObject.p_stActor->h3dData;

		if (r3dData == NULL) {
			return bonePositions;
		}

		for (int i = 0;i < Constants::GHOST_NUMBONES;i++) {

			if (r3dData->hArrayOfChannels == NULL) continue;
			int channelId = BoneToChannelIndex(i);
			if (channelId < 0) continue;
			HIE_tdstSuperObject* spo = r3dData->hArrayOfChannels[channelId].hSupObject;
			if (spo == NULL) continue;

			bonePositions[i] = BonePosToByteVec3(spo->p_stGlobalMatrix->stPos, boneSource->p_stGlobalMatrix->stPos);
		}

		return bonePositions;
	}

	std::array<Vec3, Constants::GHOST_NUMBONES> DecompressBonePositions(std::array<ByteVec3, Constants::GHOST_NUMBONES> compressedBonePositions, MTH3D_tdstVector origin)
	{
		std::array<Vec3, Constants::GHOST_NUMBONES> result;

		for (int i = 0;i < Constants::GHOST_NUMBONES;i++) {
			result[i] = ByteVec3ToBonePos(compressedBonePositions[i], origin);
		}
		
		return result;
	}
}