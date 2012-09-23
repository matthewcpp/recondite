#include "rwxContentManager.hpp"

rwxContentManager::rwxContentManager(rOpenGLGraphicsDevice* graphicsDevice){
	m_error = rCONTENT_ERROR_NONE;
	m_resource = NULL;
	m_graphicsDevice = graphicsDevice;
	m_baseAssetId = 1;
}

rwxContentManager::~rwxContentManager(){
	UnloadAssets();
}

int rwxContentManager::GetNextAssetId(){
	return ++m_baseAssetId;
}

int rwxContentManager::GetLastAssetId() const{
	return m_baseAssetId;
}

void rwxContentManager::SetBaseAssetId(int assetId){
	m_baseAssetId = assetId;
}

bool rwxContentManager::RemoveTextureAsset(rTexture2D* texture){
	wxLogMessage("unload texture Asset: %i", texture->GraphicsDeviceID());
	
	m_graphicsDevice->UnregisterTexture(texture->GraphicsDeviceID());
	m_textures.erase(texture->AssetId());
	
	return true;
}

rTexture2D* rwxContentManager::LoadWxImageToGraphicsDevice(wxImage& texture, const wxString& name, int assetId){
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
	
	rTexture2D* tex = new rTexture2D(assetId, name, size.x, size.y, textureId);
	
	rTextureMapEntry entry(assetId, tex);
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
	
	rTexture2D* tex = LoadWxImageToGraphicsDevice(texture, name, GetNextAssetId());
	
	if (tex){
		tex->SetAssetSourceInfo(rASSET_SOURCE_FILE, path);
		tex->SetDependantCount(1);
	}
	
	return tex;
}

rTexture2D* rwxContentManager::ImportTextureAssetFromInfo(rAssetInfo& info){
	wxMemoryInputStream fileStr(&info.buffer[0], info.buffer.size());
	
	wxImage texture(fileStr);
	
	if (texture.IsOk())
			wxLogMessage("Load Texture from Asset Resource.");
	
	rTexture2D* tex = LoadWxImageToGraphicsDevice(texture, info.name, info.assetId);
	
	if (tex){
		tex->SetAssetSourceInfo(rASSET_SOURCE_RESOURCE, wxEmptyString);
		tex->SetDependantCount(info.dependants);
	}
	
	return tex;
}

rTexture2D* rwxContentManager::GetTextureAsset(int assetId){
	m_error = rCONTENT_ERROR_NONE;
	
	rTextureItr tex = m_textures.find(assetId);
	if (tex != m_textures.end())
		return tex->second;
	
	if (m_resource){
		rAssetInfo info;
		if (m_resource->GetAsset(assetId, info))
			return ImportTextureAssetFromInfo (info);
	}

	m_error = rCONTENT_ERROR_RESOURCE_NOT_PRESENT;
	return NULL;
}

bool rwxContentManager::AddAssetResource(rAssetResource* resource){
	m_resource = resource;
	return true;
}

bool rwxContentManager::RemoveAssetResource(rAssetResource* resource){
	m_resource = NULL;
	return true;
}

rContentError rwxContentManager::GetError() const{
	return m_error;
}

void rwxContentManager::UnloadAssets(){
	
	rTexture2D* tex;
	for (rTextureItr it = m_textures.begin(); it != m_textures.end(); ++it){
		tex = it->second;
		m_graphicsDevice->UnregisterTexture(tex->GraphicsDeviceID());
		delete tex;
	}
	
	m_textures.clear();
}

void rwxContentManager::RetainAsset(rAsset* asset){
	m_error = rCONTENT_ERROR_NONE;
	rAssetInfo info;
	
	info.assetId = asset->AssetId();
	info.name = asset->Name();
	info.dependants = asset->Dependants() + 1;
	m_resource->UpdateAsset(info);
}

void rwxContentManager::ReleaseAsset(rAsset* asset){
	int dependants = asset->Dependants();
	rAssetInfo info;
	
	if (dependants > 1){ 
		info.assetId = asset->AssetId();
		info.name = asset->Name();
		info.dependants = dependants - 1;
		m_resource->UpdateAsset(info);
	}
	else{
		switch (asset->Type()){
			case rASSET_TEXTURE2D:
				RemoveTextureAsset(static_cast<rTexture2D*>(asset));
				break;
		}
	}
}

rAsset* rwxContentManager::GetAsset(int assetId){
	return GetTextureAsset(assetId);
}

rModel* rwxContentManager::ImportModelAssetFromFile(const rString& path, const rString& name){
	rModelData modelData;
	rwxAssimpModelImporter importer;
	bool result = importer.Import(path.c_str(), &modelData);
	
	if (result)
		return ImportModelData(modelData);
	
	return NULL;
}

rModel* rwxContentManager::ImportModelData(rModelData& modelData){
	
	
	return NULL;
}