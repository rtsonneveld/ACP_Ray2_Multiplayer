#pragma once
#include "texturemanager.h"

namespace R2MP::DSP {
	class GhostDisplay {
	private:
		GLI_tdstMaterial material;
	public:
		void Init();
		void DrawGhosts();
	};
}