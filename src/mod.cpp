#include "mod.h"
#include "display/displaymanager.h"
#include "state/statemanager.h"

namespace R2MP {

	DisplayManager displayManager;
	StateManager stateManager;

	void MOD_EngineTick() {
		LOG_PollConsole();
		NTW_PollPackets();
		GAM_fn_vEngine();
	}

	void MOD_fn_vDisplayAll() {
		displayManager.Draw(stateManager);
		GAM_fn_vDisplayAll();
	}

}