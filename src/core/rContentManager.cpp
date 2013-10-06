#include "rContentManager.hpp"

rContentManager::rContentManager(rGraphicsDevice* graphicsDevice){
	m_graphicsDevice = graphicsDevice;
	m_nextAssetId = 0;
	
	m_error = rCONTENT_ERROR_NONE;
	m_processingBatchFile = false;
}

rContentManager::~rContentManager(){
	UnloadAssets();
}

rContentError rContentManager::LoadAssetManifestFromPath(const rString& path){
	std::ifstream manifest(path.c_str());
	
	if (!manifest){
		m_error = rCONTENT_ERROR_FILE_NOT_FOUND;
	}
	else{
		m_error = LoadAssetManifestFromStream(manifest);
	}
	
	return m_error;
}

rContentError rContentManager::LoadAssetManifestFromStream(std::istream& stream){
	UnloadAssets();
	
	if (stream){
		rXMLDocument document;
		document.LoadFromStream(stream);
		
		rXMLElementArray assets;
		document.FindElements("asset", assets);
		
		m_processingBatchFile = true;
		NotifyBatchBegin(assets.size());
		LoadManifestAssets(assets);
		m_processingBatchFile = false;
		NotifyBatchEnd();
	}
	else{
		m_error = rCONTENT_ERROR_FILE_NOT_READABLE;
	}
	
	return m_error;
}

void rContentManager::LoadManifestAssets(rXMLElementArray& assets){
	rXMLElement* assetElement, *nameElement, *pathElement;
	rString name, path, typeStr;
	size_t numAssets = assets.size();
	rAssetType assetType;
	
	for (size_t i = 0; i < numAssets; i++){
		assetElement = assets[i];
		nameElement = assetElement->GetFirstChildNamed("name");
		pathElement = assetElement->GetFirstChildNamed("element");
		assetElement->GetAttribute<rString>("type", typeStr);
		
		if (nameElement && pathElement){
			assetType = rAsset::TypeForString(typeStr);
			name = nameElement->Text();
			path = pathElement->Text();
			
			switch (assetType){
			case rASSET_TEXTURE2D:
				if (GetTextureAsset(name))
					m_error = rCONTENT_ERROR_ASSET_NAME_ALREADY_PRESENT;
				else
					LoadTextureFromPath(path, name);
				break;
				
			case rASSET_SHADER:
				if (GetShaderAsset(name))
					m_error = rCONTENT_ERROR_ASSET_NAME_ALREADY_PRESENT;
				else
					LoadShaderFromPath(path, name);
				break;
				
			case rASSET_MATERIAL:
				if (GetMaterialAsset(name))
					m_error = rCONTENT_ERROR_ASSET_NAME_ALREADY_PRESENT;
				else
					LoadMaterialFromPath(path, name);
				break;
				
			default:
				m_error = rCONTENT_ERROR_UNKNOWN_ASSET_TYPE;
			};
			
			if (m_error)
				NotifyBatchLoadError(name, assetType, m_error, i, numAssets);
			else
				NotifyBatchProgress(name, assetType, i, numAssets);
		}
		else{
			m_error = rCONTENT_ERROR_PARSE_ERROR;
		}
		
	}
}

void rContentManager::UnloadAssets(){
	UnloadMaterials();
	UnloadShaders();
	UnloadTextures();
	UnloadGeometry();
	
}

void rContentManager::UnloadTextures(){
	rTexture2D* texture;
	
	for (rTextureItr it = m_textures.begin(); it != m_textures.end(); ++it){
		texture = it->second;
		m_graphicsDevice->UnregisterTexture(texture->GraphicsDeviceID());
		delete texture;
	}
	
	m_textures.clear();
}

rContentError rContentManager::RemoveTextureAsset(const rString& name){
	rTextureItr result = m_textures.find(name);
	
	if (result == m_textures.end()){
		m_error = rCONTENT_ERROR_ASSET_NOT_PRESENT;
	}

	rTexture2D* texture = result->second;
	
	if (texture->RetainCount() == 0){
		rTexture2D* texture = result->second;
		m_textures.erase(result);
		
		m_graphicsDevice->UnregisterTexture(texture->GraphicsDeviceID());
		delete texture;
		m_error = rCONTENT_ERROR_NONE;
		NotifyAssetUnloaded(name, rASSET_TEXTURE2D);
	}
	else{
		m_error = rCONTENT_ERROR_ASSET_IN_USE;
	}
	
	return m_error;
}

rTexture2D* rContentManager::LoadTexture(const rTexture2DData& textureData, const rString& name){
	rTexture2D* texture = NULL;
	
	if (m_textures.count(name))
		m_error = rCONTENT_ERROR_ASSET_NAME_ALREADY_PRESENT;
	else
		m_error = textureData.GetError();
	
	if (m_error){
		if (!m_processingBatchFile) NotifyAssetLoadError(name, rASSET_TEXTURE2D, m_error);
	}
	else
	{
		unsigned int textureId = m_graphicsDevice->CreateTexture(textureData.GetWidth(), textureData.GetHeight(), textureData.GetBPP(), textureData.GetData());
		texture = new rTexture2D(textureData.GetWidth(), textureData.GetHeight(), textureData.GetBPP(), textureId,
						GetNextAssetId(), name, textureData.GetPath());
	
		rTextureMapEntry entry(name, texture);
		m_textures.insert(entry);
		if (!m_processingBatchFile) NotifyAssetLoadComplete(name, rASSET_TEXTURE2D);
	}

	return texture;
}

rTexture2D* rContentManager::LoadTextureFromPath(const rString& path, const rString& name){
	rTexture2DData textureData(path);
	return LoadTexture(textureData, name);
}

rTexture2D* rContentManager::GetTextureAsset(const rString& name) const{
	rTextureConstItr result = m_textures.find(name);
	
	if (result == m_textures.end())
		return NULL;
	else
		return result->second;
}

rShader* rContentManager::GetShaderAsset(const rString& name) const{
	rShaderConstItr result = m_shaders.find(name);
	
	if (result == m_shaders.end())
		return NULL;
	else
		return result->second;
}

rShader* rContentManager::LoadShaderFromPath(const rString& path, const rString& name){
	rShaderData shaderData(path);
	return LoadShader(shaderData, name);
}

rShader* rContentManager::LoadShader(const rShaderData& shaderData, const rString& name){
	rShader* shader = NULL;
	
	if (m_shaders.count(name))
		m_error = rCONTENT_ERROR_ASSET_NAME_ALREADY_PRESENT;
	else
		m_error = shaderData.GetError();
	
	if (m_error){
		if (!m_processingBatchFile) NotifyAssetLoadError(name, rASSET_SHADER, m_error);
	}
	else
	{
		unsigned int shaderId = m_graphicsDevice->CreateShaderProgram(shaderData.GetVertexProgram(), shaderData.GetFragmentProgram());
	
		if (shaderId != 0){
			shader = new rShader(shaderId, GetNextAssetId(), name, shaderData.GetPath());
			rShadermapEntry entry(name, shader);
			m_shaders.insert(entry);
			if (!m_processingBatchFile) NotifyAssetLoadComplete(name, rASSET_SHADER);
		}
	}
	
	return shader;
}

rContentError rContentManager::RemoveShaderAsset(const rString& name){
	rShaderItr result = m_shaders.find(name);
	
	if (result == m_shaders.end()){
		m_error = rCONTENT_ERROR_ASSET_NOT_PRESENT;
		return m_error;
	}
	
	rShader* shader = result->second;
	
	if (shader->RetainCount() == 0){
		m_graphicsDevice->DeleteShaderProgram(shader->ProgramId());
		m_shaders.erase(result);
		delete shader;
		m_error = rCONTENT_ERROR_NONE;
		NotifyAssetUnloaded(name, rASSET_SHADER);
	}
	else{
		m_error = rCONTENT_ERROR_ASSET_IN_USE;
	}
	
	return m_error;
}

size_t rContentManager::NumShaders() const{
	return m_shaders.size();
}

void rContentManager::UnloadShaders(){
	rShader* shader;
	
	for (rShaderItr it = m_shaders.begin(); it != m_shaders.end(); ++it){
		shader = it->second;
		m_graphicsDevice->DeleteShaderProgram(shader->ProgramId());
		delete shader;
	}
	
	m_shaders.clear();
}

rMaterial* rContentManager::GetMaterialAsset(const rString& name) const{
	rMaterialConstItr result = m_materials.find(name);
	
	if (result == m_materials.end())
		return NULL;
	else
		return result->second;
}

rShader* rContentManager::GetOrLoadShader(const rString& shaderName, const rString& shaderPath){
	rShader* shader = GetShaderAsset(shaderName);
	
	if (!shader){
		rShaderData shaderData(shaderPath);
		shader = LoadShader(shaderData, shaderName);
	}
	
	return shader;
}

rTexture2D* rContentManager::GetOrLoadTexture(const rString& textureName, const rString& texturePath){
	rTexture2D* texture = GetTextureAsset(textureName);
	
	if (!texture)
		texture = LoadTextureFromPath(texturePath, textureName);
	
	return texture;
}

bool rContentManager::LoadMaterialDependencies(const rMaterialData& materialData, rMaterial* material){
	rTextureArray loadedTextures;
	rArrayString materialParams;
	rMaterialParameterData paramData;
	
	materialData.GetParameterNames(materialParams);
	
	for (size_t i = 0; i < materialParams.size(); i++){
		materialData.GetParameterData(materialParams[i], paramData);
		
		switch (paramData.type){
			case rMATERIAL_PARAMETER_TEXTURE2D:{
				rTexture2D* texture = GetOrLoadTexture(paramData.value, paramData.path);
				
				if (texture){
					loadedTextures.push_back(texture);
					texture->Retain();
					material->SetTexture(materialParams[i], texture);
				}
				else{ //if there is an error, release all textures we have loaded and return false
					for (size_t t = 0; t < loadedTextures.size(); t++){
						ReleaseAsset(loadedTextures[t]);
					}
					
					return false;
				}
			}
			break;
			
			case rMATERIAL_PARAMETER_COLOR:{
				std::stringstream stream(paramData.value);
				unsigned int c[4];
				stream >> c[0] >> c[1] >> c[2] >> c[3];
				rColor color(c[0], c[1], c[2], c[3]);
				material->SetColor(materialParams[i], color);
			}
			break;
		};
	}
	
	return true;
}


rMaterial* rContentManager::LoadMaterialFromPath(const rString& path, const rString& name){
	rMaterialData materialData(path);
	return LoadMaterial(materialData, name);
}

rMaterial* rContentManager::LoadMaterial(const rMaterialData& materialData, const rString& name){
	rMaterial* material = NULL;
	
	if (m_materials.count(name))
		m_error = rCONTENT_ERROR_ASSET_NAME_ALREADY_PRESENT;
	else
		m_error = materialData.GetError();
	
	if (m_error){
		if (!m_processingBatchFile) NotifyAssetLoadError(name, rASSET_MATERIAL, m_error);
	}
	else
	{
		rShader* shader = GetOrLoadShader(materialData.GetShaderName(), materialData.GetShaderPath());
		
		if (!shader){
			m_error = rCONTENT_ERROR_UNABLE_TO_LOAD_DEPENDENCY;
			return NULL;
		}
		
		shader->Retain();
		material = new rMaterial(shader, GetNextAssetId(), name, materialData.GetPath());
		
		if (LoadMaterialDependencies(materialData, material)){
			rMaterialMapEntry entry(name, material);
			m_materials.insert(entry);
			if (!m_processingBatchFile) NotifyAssetLoadComplete(name, rASSET_MATERIAL);
		}
		else{
			ReleaseAsset(shader);
			delete material;
			material = NULL;
			m_error = rCONTENT_ERROR_UNABLE_TO_LOAD_DEPENDENCY;
		}
	}
	
	return material;
}

rContentError rContentManager::RemoveMaterialAsset(const rString& name){
	rMaterialItr result = m_materials.find(name);
	
	if (result == m_materials.end()){
		m_error = rCONTENT_ERROR_ASSET_NOT_PRESENT;
	}
	
	rMaterial* material = result->second;
	if (material->RetainCount() == 0){
		rArrayString parameterNames;
		rMaterialParameter parameter;
		material->GetParameterNames(parameterNames);
		
		for (size_t i = 0; i < parameterNames.size(); i++){
			material->GetParameter(parameterNames[i], parameter);
			if (parameter.m_type == rMATERIAL_PARAMETER_TEXTURE2D)
				ReleaseAsset(parameter.GetTexture());
		}
			
		delete material;
		m_error = rCONTENT_ERROR_NONE;
		NotifyAssetUnloaded(name, rASSET_MATERIAL);
	}
	
	return m_error;
}

void rContentManager::UnloadMaterials(){
	//todo: implement me
}

void rContentManager::ReleaseAsset(rAsset* asset){
	int retainCount = asset->Release();
	
	if (retainCount == 0){
		switch (asset->Type()){
			case rASSET_TEXTURE2D:
				RemoveTextureAsset(asset->Name());
				break;
			case rASSET_SHADER:
				RemoveShaderAsset(asset->Name());
				break;
			case rASSET_MATERIAL:
				RemoveMaterialAsset(asset->Name());
				break;
			case rASSET_GEOMETRY:
				RemoveGeometryAsset(asset->Name());
				break;
			default:
				break;
		};
	}
}

size_t rContentManager::NumMaterials() const{
	return m_materials.size();
}


rContentError rContentManager::GetLastError() const{	
	return m_error;
}

size_t rContentManager::NumTextures() const{
	return m_textures.size();
}

int rContentManager::GetNextAssetId(){
	return ++m_nextAssetId; 
}

void rContentManager::AddListener(rContentListener* listener){
	m_listeners.push_back(listener);
}

void rContentManager::RemoveListener(rContentListener* listener){
	rContentListener* curListener;
	for (rContentListenerItr it = m_listeners.begin(); it != m_listeners.end(); ++it){
		curListener = *it;
		
		if (curListener == listener){
			m_listeners.erase(it);
			return;
		}
	}
}


rGeometry* rContentManager::GetGeometryAsset(const rString& name) const{
	rGeometry* geometry = NULL;
	
	rGeometryMap::const_iterator result = m_geometry.find(name);
	
	if (result != m_geometry.end()){
		geometry = result->second;
	}
	
	return geometry;
}

rGeometry* rContentManager::LoadGeometry(const rGeometryData& geometryData, const rString& name){
	rGeometry* geometry = NULL;

	if (m_geometry.count(name))
		m_error = rCONTENT_ERROR_ASSET_NAME_ALREADY_PRESENT;
	else
		m_error = geometryData.GetError();
	
	if (m_error){
		if (!m_processingBatchFile) NotifyAssetLoadError(name, rASSET_GEOMETRY, m_error);
	}
	else
	{
		unsigned int vertexBuffer = m_graphicsDevice->CreateVertexBuffer(geometryData.GetVertexData(), geometryData.VertexDataSize());
		geometry = new rGeometry(vertexBuffer, geometryData.HasTextureCoords(), geometryData.HasNormals(), GetNextAssetId(), name, geometryData.Path());
		
		rArrayString bufferNames;
		geometryData.GetElementBufferNames(bufferNames);
		
		for (size_t i = 0; i < bufferNames.size(); i++){
			rElementBufferData* buffer = geometryData.GetElementBuffer(bufferNames[i]);
			
			unsigned int elementBufferId = m_graphicsDevice->CreateElementBuffer(buffer->GetElementData(), buffer->ElementDataSize());
			geometry->AddElementBuffer(bufferNames[i], elementBufferId, buffer->ElementCount());
		}
		
		
		
		m_geometry[name] = geometry;
	}
	
	return geometry;
}

void rContentManager::DeleteGeometryBuffers(rGeometry* geometry){
	m_graphicsDevice->DeleteBuffer(geometry->VertexBufferId());
	
	rArrayString bufferNames;
	rElementBuffer elementBuffer;
	geometry->GetElementBufferNames(bufferNames);
	
	for (size_t i = 0; i < bufferNames.size(); i++){
		geometry->GetElementBuffer(bufferNames[i], elementBuffer);
		m_graphicsDevice->DeleteBuffer(elementBuffer.BufferId());
	}
	
}

rContentError rContentManager::RemoveGeometryAsset(const rString& name){
	rGeometryMap::iterator result = m_geometry.find(name);
	
	if (result != m_geometry.end()){
		rGeometry* geometry = result->second;
		
		DeleteGeometryBuffers(geometry);
		delete geometry;
		m_geometry.erase(result);
		
		m_error = rCONTENT_ERROR_NONE;
	}
	else{
		m_error = rCONTENT_ERROR_ASSET_NOT_PRESENT;
	}
	
	return m_error;
}

void rContentManager::UnloadGeometry(){
	for (rGeometryMap::iterator it = m_geometry.begin(); it != m_geometry.end(); ++it){
		rGeometry* geometry = it->second;
		
		DeleteGeometryBuffers(geometry);
		delete geometry;
	}
	
	m_geometry.clear();
}

size_t rContentManager::NumGeometry() const{
	return m_geometry.size();
}

void rContentManager::NotifyBatchBegin(int total) {
	for (rContentListenerItr it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->BeginBatchLoad(total);
}

void rContentManager::NotifyBatchProgress(const rString& assetName, rAssetType type, int current, int total) {
	for (rContentListenerItr it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->BatchLoadProgress(assetName, type, current, total);
}

void rContentManager::NotifyBatchLoadError(const rString& assetName, rAssetType type, rContentError error, int current, int total){
	for (rContentListenerItr it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->BatchLoadError(assetName, type, error, current, total);
}

void rContentManager::NotifyBatchEnd(){
	for (rContentListenerItr it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->EndBatchLoad();
}

void rContentManager::NotifyAssetLoadComplete(const rString& assetName, rAssetType type){
	for (rContentListenerItr it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->AssetLoadComplete(assetName, type);
}

void rContentManager::NotifyAssetLoadError(const rString& assetName, rAssetType type, rContentError error){
	for (rContentListenerItr it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->AssetLoadError(assetName, type, error);
}

void rContentManager::NotifyAssetUnloaded(const rString& assetName, rAssetType type){
	for (rContentListenerItr it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->AssetUnloaded(assetName, type);
}

bool rContentManager::ProcessingBatchFile() const{
	return m_processingBatchFile;
}
	
void rContentManager::Init() {}
void rContentManager::Uninit() {}
void rContentManager::InitDefaultAssets() {}
