#include "mod.h"
#include "util/vector.h"
#include "display/displaymanager.h"
#include "display/texturemanager.h"
#include "network/packet/serverbound_play_packets.h"
#include "bonetools.h"
#include "constants.h"
#include "cpa/actorutil.h"
#include "cpa/dsgvarnames.h"
#include <array>
#include <bitset>

namespace R2MP {

	std::string lastLevel = "Unknown";

	typedef std::bitset<Constants::GLOBAL_BITS_NUMBITS> tdGlobalBits;

	tdGlobalBits lastGlobalBits;

	void EngineTick() {
		// Every tick while connected send updated position and level information!
		HIE_tdstSuperObject* pRayman = HIE_fn_p_stFindObjectByName("Rayman");
		HIE_tdstSuperObject* pGlobal  = HIE_fn_p_stFindObjectByName("global");

		HIE_tdstSuperObject* pBoneSource = DetermineBoneSource();

		if (pRayman && pGlobal && NET::IsConnectedToServer()) {
			auto networking = NET::GetServerboundConnection();
			std::string level = std::string(GAM_fn_p_szGetLevelName());

			tdGlobalBits globalBits = *CPA::Actor::GetDsgVarPtr<tdGlobalBits>
				(pGlobal->hLinkedObject.p_stActor, CPA::DsgVar::Global::GLOBAL_Bits);

			MTH3D_tdstVector* pCoords = &pBoneSource->p_stGlobalMatrix->stPos;
			Vec3 position = Vec3{ pCoords->x, pCoords->y, pCoords->z };
			auto ghostBonePositions = GetCompressedBonePositions(pBoneSource);

			if (level != lastLevel) {
				lastLevel = level;
				NET::ServerboundChangeLevelPacket packet{
					.levelName = level
				};
				networking->Send(packet);
			}

			if (globalBits != lastGlobalBits) {
				lastGlobalBits = globalBits;
				NET::ServerboundUpdateGlobalBitsPacket packet{
					.globalBits = globalBits
				};
				networking->Send(packet);
			}

			NET::ServerboundMovePacket packet {
				.position = position,
				.ghostBonePositions = ghostBonePositions
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