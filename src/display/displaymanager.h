#pragma once

#include "../state/statemanager.h"

namespace R2MP {
	class DisplayManager {
	public:
		void Initialize();
		void Draw(StateManager& stateManager);
	};
}