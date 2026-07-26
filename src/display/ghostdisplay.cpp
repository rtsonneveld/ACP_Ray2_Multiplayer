#include "ghostdisplay.h"
#include "../state/statemanager.h"
#include "../client/playermanager.h"
#include <ACP_Ray2.h>

namespace R2MP::DSP {

	void GhostDisplay::Init() {
		material.p_stTexture = DSP::GetTextureManager().GetTexture("textures_personnages\\divers\\lums_corps_mauve_ad_mxy.tga");
		material.ulMaterialType = GLI_C_Mat_lIsSolid;
	}

	void GhostDisplay::DrawGhosts() {

		auto& playerManager = CLI::GetPlayerManager();
		for (auto& player : playerManager.GetPlayers()) {

			GLI_vDrawWorldSprite((float*)&player.position, &material, 1.0f, 1.0f,
				&GAM_g_stEngineStructure->stViewportAttr, 0);
		}
	};
}