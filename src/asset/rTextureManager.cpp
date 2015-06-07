#include "asset/rTextureManager.hpp"

rTextureManager::rTextureManager(rGraphicsDevice* graphicsDevice, rFileSystem* fileSystem)
	:rAssetManager<rTexture, rTextureData, rTextureFile>(fileSystem)
{
	m_graphicsDevice = graphicsDevice;
}

rTexture* rTextureManager::CreateAssetFromData(const rTextureData& textureData, const rString& name){
	unsigned int textureId = m_graphicsDevice->CreateTexture(textureData.Width(), textureData.Height(), textureData.Bpp(), textureData.Data());
	return new rTexture(name, textureData.Width(), textureData.Height(), textureData.Bpp(), textureId);
}

void rTextureManager::DisposeAsset(rTexture* texture){
	m_graphicsDevice->UnregisterTexture(texture->GraphicsDeviceID());
}