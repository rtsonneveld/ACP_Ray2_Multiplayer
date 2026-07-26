#include "displaymanager.h"
#include "../client/playermanager.h"

namespace R2MP::DSP {

	// Singleton
	DisplayManager displayManager;

	void DisplayManager::Init() {
		ghostDisplay.Init();
	}
	void DisplayManager::Draw() {

		ghostDisplay.DrawGhosts();
	}


	DisplayManager& GetDisplayManager() {
		return displayManager;
	}
}