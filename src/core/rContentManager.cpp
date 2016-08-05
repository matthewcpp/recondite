#include "rContentManager.hpp"

rContentManager::rContentManager(rGraphicsDevice* graphicsDevice, rFileSystem* fileSystem){
	m_graphicsDevice = graphicsDevice;
	m_fileSystem = fileSystem;

	m_textures.reset(new rTextureManager(graphicsDevice, fileSystem));
	m_shaders.reset(new rShaderManager(graphicsDevice, fileSystem));
	m_fonts.reset(new rFontManager(fileSystem, m_textures.get()));
	m_models.reset(new rModelManager(m_fileSystem, m_graphicsDevice));
}

void rContentManager::Clear(){
	m_textures->Clear();
	m_shaders->Clear();
	m_fonts->Clear();
	m_models->Clear();
}

rFileSystem* rContentManager::FileSystem(){
	return m_fileSystem;
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