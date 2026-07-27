#include "ghostdisplay.h"
#include "../client/playermanager.h"
#include "../common/playerdata.h"
#include "../bonetools.h"

#include <ACP_Ray2.h>

namespace R2MP::DSP {

	void GhostDisplay::Init() {

		GLI_tdstTexture* textures[Constants::GHOST_NUMBONES] = {
			DSP::GetTextureManager().GetTexture("textures_personnages\\divers\\lums_corps_mauve_ad_mxy.tga"), // Body
			DSP::GetTextureManager().GetTexture("textures_personnages\\divers\\lums_corps_blanc_ad_mxy.tga"), // Right hand
			DSP::GetTextureManager().GetTexture("textures_personnages\\divers\\lums_corps_blanc_ad_mxy.tga"), // Left hand
			DSP::GetTextureManager().GetTexture("textures_personnages\\divers\\lums_corps_ad_mxy.tga"), // Right foot
			DSP::GetTextureManager().GetTexture("textures_personnages\\divers\\lums_corps_ad_mxy.tga"),  // Left foot
			DSP::GetTextureManager().GetTexture("textures_personnages\\divers\\lums_corps_ad_mxy.tga")  // Head
		};

		for (int i = 0;i < Constants::GHOST_NUMBONES;i++) {
			materials[i].p_stTexture = textures[i];
			materials[i].ulMaterialType = GLI_C_Mat_lIsSolid;
		}
	}

	void GhostDisplay::DrawGhosts() {

		auto& playerManager = CLI::GetPlayerManager();
		for (auto& player : playerManager.GetPlayers()) {

			
			CommonPlayerData playerData = player.data;
			auto bonePositions = DecompressBonePositions(playerData.ghostBonePositions, playerData.position);

			for (int i = 0;i < Constants::GHOST_NUMBONES;i++) {

				Vec3 bonePos = bonePositions[i];
				bonePos.z += boneDisplayInfo[i].offsetZ;

				GLI_vDrawWorldSprite((float*)&bonePos, &materials[i], boneDisplayInfo[i].sizeX, boneDisplayInfo[i].sizeY,
					&GAM_g_stEngineStructure->stViewportAttr, 0);
			}
		}
	};
}