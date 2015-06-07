#include "rContentManager.hpp"

rContentManager::rContentManager(rGraphicsDevice* graphicsDevice, rFileSystem* fileSystem){
	m_graphicsDevice = graphicsDevice;
	m_fileSystem = fileSystem;

	m_textures.reset(new rTextureManager(graphicsDevice, fileSystem));
	m_shaders.reset(new rShaderManager(graphicsDevice, fileSystem));
	m_geometry.reset(new rGeometryManager(graphicsDevice, fileSystem));
	m_materials.reset(new rMaterialManager(fileSystem, m_textures.get(), m_shaders.get()));
	m_fonts.reset(new rFontManager(fileSystem, m_textures.get()));
	m_models.reset(new rModelManager(m_fileSystem, m_materials.get(), m_shaders.get(), m_geometry.get()));
}

void rContentManager::Clear(){
	m_textures->Clear();
	m_shaders->Clear();
	m_geometry->Clear();
	m_materials->Clear();
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

rGeometryManager* rContentManager::Geometry(){
	return m_geometry.get();
}

rMaterialManager* rContentManager::Materials(){
	return m_materials.get();
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