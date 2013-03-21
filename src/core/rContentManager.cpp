#include "rContentManager.hpp"

rContentManager::rContentManager(rGraphicsDevice* graphicsDevice){
	m_graphicsDevice = graphicsDevice;
}

rContentManager::~rContentManager(){
	UnloadAssets();
}

void rContentManager::UnloadAssets(){
}

bool rContentManager::RemoveTextureAsset(const rString& name){
	return true;
}

rTexture2D* rContentManager::ImportTextureAssetFromFile(const rString& path , const rString& name){
	return NULL;
}

rTexture2D* rContentManager::GetTextureAsset(const rString& name){
	return NULL;
}
