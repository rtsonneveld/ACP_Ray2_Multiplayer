#include "displaymanager.h"
#include "../client/playermanager.h"
#include <ACP_Ray2.h>

namespace R2MP {

	void DisplayManager::Initialize() {

	}
	void DisplayManager::Draw(StateManager& stateManager) {
		auto& playerManager = CLI::GetPlayerManager();
		for (auto& player : playerManager.GetPlayers()) {
			// TODO Replace with rendering code
			LOG::Print("Player %s is at X: %f, Y: %f, Z: %f", player.username.data(), player.position.x, player.position.y, player.position.z);
		}
	}
}