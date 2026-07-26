#pragma once
#include "../state/statemanager.h"
#include "texturemanager.h"
#include "ghostdisplay.h"

namespace R2MP::DSP {
	class DisplayManager {

	private:
		GhostDisplay ghostDisplay;

	public:
		void Init();
		void Draw();
	};

	DisplayManager& GetDisplayManager();
}