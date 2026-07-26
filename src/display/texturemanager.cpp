#include "texturemanager.h"
#include <ACP_Ray2.h>

namespace R2MP::DSP {

	// Singleton
	TextureManager textureManager;

	GLI_tdstTexture* TextureManager::GetTexture(std::string filename)
	{
		// Texture in cache? Return that
		if (TextureCache.find(filename) != TextureCache.end()) {
			return TextureCache[filename];
		}

		GLI_tdstTexture* foundTexture = GLI_fn_pstFindTexture(filename.c_str());
		if (foundTexture != nullptr) {

			TextureCache[filename] = foundTexture;
			return foundTexture;
		}


		GLI_tdstTexture* texture = (GLI_tdstTexture*)calloc(1, sizeof(GLI_tdstTexture));

		if (!GLI_fn_bReadTextureGF(texture, filename.c_str())) {
			free(texture);
			return nullptr;
		}

		TextureCache[filename] = texture;
		return texture;
	}

	void TextureManager::LoadTextures() {

		for (auto& [name, texture] : TextureCache) {
			GLI_fn_vLoadTextureInTable(texture);
		}
	}

	TextureManager& GetTextureManager() {
		return textureManager;
	}
}