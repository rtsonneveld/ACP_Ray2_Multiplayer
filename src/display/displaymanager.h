#pragma once

class StateManager;

namespace R2MP {
	class DisplayManager {
	public:
		void Initialize();
		void Draw(StateManager& stateManager);
	};
}