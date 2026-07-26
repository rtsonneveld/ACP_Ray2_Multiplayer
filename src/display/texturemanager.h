#pragma once
#include <unordered_map>
#include <string>
#include <ACP_Ray2.h>

namespace R2MP::DSP {
	class TextureManager {
	private: 
		std::unordered_map<std::string, GLI_tdstTexture*> TextureCache;
	public:
		GLI_tdstTexture* GetTexture(std::string filename);
		void LoadTextures();
	};

	TextureManager& GetTextureManager();
}