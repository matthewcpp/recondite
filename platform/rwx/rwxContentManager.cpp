#include "rwxContentManager.hpp"

rwxContentManager::rwxContentManager(rOpenGLGraphicsDevice* graphicsDevice){
	m_error = rCONTENT_ERROR_NONE;
	m_graphicsDevice = graphicsDevice;
}

rwxContentManager::~rwxContentManager(){
	UnloadAssets();
}

rTexture2D* rwxContentManager::GetTextureAsset(const rString& name){
	rTextureItr result = m_textures.find(name);
	
	if (result == m_textures.end()){
		m_error = rCONTENT_ERROR_FILE_NOT_FOUND;
		return NULL;
	}

	m_error = rCONTENT_ERROR_NONE;
	return result->second;
}

bool rwxContentManager::RemoveTextureAsset(const rString& name){
	rTextureItr result = m_textures.find(name);
	
	if (result == m_textures.end()){
		m_error = rCONTENT_ERROR_FILE_NOT_FOUND;
		return false;
	}

	rTexture2D* texture = result->second;
	
	wxLogMessage("unload texture Asset: %i", result->second->GraphicsDeviceID());	
	
	m_graphicsDevice->UnregisterTexture(texture->GraphicsDeviceID());
	m_textures.erase(texture->Name());
	
	m_error = rCONTENT_ERROR_NONE;
	return true;
}

rTexture2D* rwxContentManager::LoadWxImageToGraphicsDevice(wxImage& texture, const wxString& name){
	if (!texture.IsOk()){
		m_error = rCONTENT_ERROR_FILE_NOT_READABLE;
		return NULL;
	}
	
	//need to fix this...make it 1 call...
	texture = texture.Mirror(false);
	rwxUtils::MirrorWxImageInPlace(texture);
	
	unsigned int textureId;
	wxSize size = texture.GetSize();
	int bpp = texture.HasAlpha() ? 4 : 3;
	
	if (bpp == 4){
		rUnsigedByteArray data;
		rwxUtils::FormatWxImageDataForOpenGL(texture, data);
		textureId = m_graphicsDevice->CreateTexture(size.x, size.y, bpp, &data[0]);
	}
	else
		textureId = m_graphicsDevice->CreateTexture(size.x, size.y, bpp, texture.GetData());
	
	rTexture2D* tex = new rTexture2D(name, size.x, size.y, textureId);
	
	rTextureMapEntry entry(name, tex);
	m_textures.insert(entry);
	
	return tex;
}

rTexture2D* rwxContentManager::ImportTextureAssetFromFile(const rString& path , const rString& name){
	
	if (!wxFileExists(path)){
		m_error = rCONTENT_ERROR_FILE_NOT_FOUND;
		return NULL;
	}
	
	wxImage texture(path);
	if (texture.IsOk())
		wxLogMessage("Load Texture from File.");
	
	rTexture2D* tex = LoadWxImageToGraphicsDevice(texture, name);
	
	return tex;
}

rContentError rwxContentManager::GetError() const{
	return m_error;
}

void rwxContentManager::UnloadTextures(){
	for (rTextureItr it = m_textures.begin(); it != m_textures.end(); ++it)
		m_graphicsDevice->UnregisterTexture(it->second->GraphicsDeviceID());
	
	m_textures.clear();
}

void rwxContentManager::UnloadAssets(){
	UnloadTextures();
}