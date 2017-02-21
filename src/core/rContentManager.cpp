#include "rContentManager.hpp"

rContentManager::rContentManager(rGraphicsDevice* graphicsDevice, rFileSystem* fileSystem, iResourceManager* resourceManager){
	m_graphicsDevice = graphicsDevice;
	m_resourceManager = resourceManager;

	m_textures.reset(new rTextureManager(graphicsDevice, fileSystem));
	m_shaders.reset(new rShaderManager(graphicsDevice, fileSystem));
	m_fonts.reset(new rFontManager(fileSystem, m_textures.get()));
	m_models.reset(new rModelManager(fileSystem, resourceManager, graphicsDevice, m_textures.get(), &m_eventHandler));
}

void rContentManager::Clear(){
	m_textures->Clear();
	m_shaders->Clear();
	m_fonts->Clear();
	m_models->Clear();
}

rTextureManager* rContentManager::Textures(){
	return m_textures.get();
}

rShaderManager* rContentManager::Shaders(){
	return m_shaders.get();
}

rFontManager* rContentManager::Fonts(){
	return m_fonts.get();
}

rModelManager* rContentManager::Models(){
	return m_models.get();
}

rContentManager::~rContentManager(){
	Clear();
}

bool rContentManager::LoadFromManifest(const recondite::AssetManifest& contentData) {
	size_t count = contentData.Count(rAssetType::Model);
	rString name, path;

	for (size_t i = 0; i < count; i++) {
		contentData.Get(rAssetType::Model, i, name, path);
		m_models->LoadFromResource(path, name);
	}

	return true;
}

rEventHandler* rContentManager::Events() {
	return &m_eventHandler;
}