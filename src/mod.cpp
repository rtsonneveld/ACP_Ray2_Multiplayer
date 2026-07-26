#include "mod.h"
#include "util/vector.h"
#include "display/displaymanager.h"
#include "display/texturemanager.h"
#include "state/statemanager.h"
#include "network/packet/serverbound_play_packets.h"

namespace R2MP {
	StateManager stateManager;

	std::string lastLevel = "Unknown";

	void EngineTick() {
		// Every tick while connected send updated position and level information!
		HIE_tdstSuperObject* pRayman = HIE_fn_p_stFindObjectByName("Rayman");
		if (pRayman && NET::IsConnectedToServer()) {
			auto networking = NET::GetServerboundConnection();
			std::string level = std::string(GAM_fn_p_szGetLevelName());
			MTH3D_tdstVector* pCoords = &pRayman->p_stGlobalMatrix->stPos;
			Vec3 position = Vec3{ pCoords->x, pCoords->y, pCoords->z };
			if (level != lastLevel) {
				lastLevel = level;
				NET::ServerboundChangeLevelPacket packet{
					.levelName = level
				};
				networking->Send(packet);
			}
			NET::ServerboundMovePacket packet{
				.position = position
			};
			networking->Send(packet);
		}

		LOG::PollConsole();
		NET::PollPackets();
		GAM_fn_vEngine();
	}

	bool displayInitialized = false;

	void DisplayAll() {

		if (!displayInitialized) {
			DSP::GetDisplayManager().Init();
			displayInitialized = true;
		}

		DSP::GetDisplayManager().Draw();
		GAM_fn_vDisplayAll();
	}
	
	void ComputeTextures() {
		// Whenever the map changes, before textures get computed, load the textures we want
		DSP::GetTextureManager().LoadTextures();

		GLI_vComputeTextures();
	}

}