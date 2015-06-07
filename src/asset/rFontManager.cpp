#include "asset/rFontManager.hpp"

rFontManager::rFontManager(rFileSystem* fileSystem, rTextureManager* textureManager)
	:rAssetManager < rFont, rFontData, rFontFile >(fileSystem)
{
	m_textureManager = textureManager;
}

rFont* rFontManager::CreateAssetFromData(const rFontData& fontData, const rString& name) {
	return nullptr;
}

void rFontManager::DisposeAsset(rFont* rFont) {
}