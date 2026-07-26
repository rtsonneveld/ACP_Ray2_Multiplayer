#include "mod.h"
#include "display/displaymanager.h"
#include "state/statemanager.h"

namespace R2MP {
	DisplayManager displayManager;
	StateManager stateManager;

	void EngineTick() {
		LOG::PollConsole();
		NET::PollPackets();
		GAM_fn_vEngine();
	}

	void DisplayAll() {
		displayManager.Draw(stateManager);
		GAM_fn_vDisplayAll();
	}

}