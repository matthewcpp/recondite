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

void rContentManager::LoadAssetManifest(const rAssetManifestData& assetManifest){
	m_processingBatchFile = true;

	size_t assetCount = assetManifest.AssetCount();
	rString manifestPath = assetManifest.GetPath();
	rAssetManifestEntry* entry = NULL;

	NotifyManifestBegin(manifestPath, assetManifest.AssetCount());

	for (size_t i =0; i < assetCount; i++){
		entry = assetManifest.GetManifestEntry(i);

		switch (entry->type){
			case rASSET_TEXTURE2D:
				LoadTextureFromPath(entry->path, entry->name);
				break;

			case rASSET_SHADER:
				LoadShaderFromPath(entry->path, entry->name);
				break;

			case rASSET_MATERIAL:
				LoadMaterialFromPath(entry->path, entry->name);
				break;

			case rASSET_GEOMETRY:
				LoadGeometryFromPath(entry->path, entry->name);
				break;

			case rASSET_FONT:
				LoadFontFromPath(entry->path, entry->name);
				break;

			case rASSET_MODEL:
				LoadModelFromPath(entry->path, entry->name);
				break;

			default:
				m_error = rCONTENT_ERROR_UNKNOWN_ASSET_TYPE;
		};

		if (m_error)
			NotifyManifestLoadError(entry->type, entry->name, entry->path, m_error, i, assetCount);
		else
			NotifyManifestProgress(entry->type, entry->name, entry->path, i, assetCount);
	}

	m_processingBatchFile = false;
	NotifyManifestEnd(manifestPath);
}

void rContentManager::LoadAssetManifestFromPath(const rString& path){
	rAssetManifestData manifestData;
	rAssetManifestDataReader reader;
	
	rContentError error = reader.ReadFromFile(path, manifestData);

	if (!error)
		LoadAssetManifest(manifestData);
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
		NotifyAssetUnloaded(rASSET_TEXTURE2D, name);
	}
	else{
		m_error = rCONTENT_ERROR_ASSET_IN_USE;
	}
	
	return m_error;
}

rTexture2D* rContentManager::LoadTexture(const rTexture2DData& textureData, const rString& name){
	rTexture2D* texture = NULL;
	
	if (m_textures.count(name)){
		m_error = rCONTENT_ERROR_ASSET_NAME_ALREADY_PRESENT;
	}
	else
	{
		unsigned int textureId = m_graphicsDevice->CreateTexture(textureData.GetWidth(), textureData.GetHeight(), textureData.GetBPP(), textureData.GetData());
		texture = new rTexture2D(textureData.GetWidth(), textureData.GetHeight(), textureData.GetBPP(), textureId,
						GetNextAssetId(), name, textureData.GetPath());
	
		rTextureMapEntry entry(name, texture);
		m_textures.insert(entry);
		if (!m_processingBatchFile) NotifyAssetLoadComplete(rASSET_TEXTURE2D, name, textureData.GetPath());
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
	{
		unsigned int shaderId = m_graphicsDevice->CreateShaderProgram(shaderData.GetVertexProgram(), shaderData.GetFragmentProgram());
	
		if (shaderId != 0){
			shader = new rShader(shaderId, GetNextAssetId(), name, shaderData.GetPath());
			rShadermapEntry entry(name, shader);
			m_shaders.insert(entry);
			if (!m_processingBatchFile) NotifyAssetLoadComplete(rASSET_SHADER, name, shaderData.GetPath());
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
		NotifyAssetUnloaded(rASSET_SHADER, name);
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

rShader* rContentManager::GetOrLoadShader(const rString& name, const rString& path){
	rShader* shader = GetShaderAsset(name);
	
	if (!shader){
		shader = LoadShaderFromPath(path, name);
	}
	
	return shader;
}

rGeometry* rContentManager::GetOrLoadGeometry(const rString& name, const rString& path){
	rGeometry* geometry = GetGeometryAsset(name);

	if (!geometry){
		geometry = LoadGeometryFromPath(path, name);
	}

	return geometry;
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
	rString materialDirectory = rPath::Directory(materialData.GetPath());
	
	for (size_t i = 0; i < materialParams.size(); i++){
		materialData.GetParameterData(materialParams[i], paramData);
		
		switch (paramData.type){
			case rMATERIAL_PARAMETER_TEXTURE2D:{
				rTexture2D* texture = GetOrLoadTexture(paramData.value, rPath::Combine(materialDirectory, paramData.path));
				
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
				std::stringstream stream(paramData.value.c_str());
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

rMaterial* rContentManager::GetOrLoadMaterial(const rString& name, const rString& path){
	rMaterial* material = GetMaterialAsset(name);

	if (!material){
		material = LoadMaterialFromPath(path, name);
	}

	return material;
}

rMaterial* rContentManager::LoadMaterial(const rMaterialData& materialData, const rString& name){
	rMaterial* material = NULL;
	
	if (m_materials.count(name)){
		m_error = rCONTENT_ERROR_ASSET_NAME_ALREADY_PRESENT;
	}
	else
	{
		rString materialDirectory = rPath::Directory(materialData.GetPath());
		rString shaderPath = rPath::Combine(materialDirectory, materialData.GetShaderPath());
		rShader* shader = GetOrLoadShader(materialData.GetShaderName(), shaderPath);
		
		if (!shader){
			m_error = rCONTENT_ERROR_UNABLE_TO_LOAD_DEPENDENCY;
			return NULL;
		}
		
		shader->Retain();
		material = new rMaterial(shader, GetNextAssetId(), name, materialData.GetPath());
		
		if (LoadMaterialDependencies(materialData, material)){
			rMaterialMapEntry entry(name, material);
			m_materials.insert(entry);
			if (!m_processingBatchFile) NotifyAssetLoadComplete(rASSET_MATERIAL, name, materialData.GetPath());
		}
		else{
			ReleaseAsset(shader);
			delete material;
			material = NULL;
			m_error = rCONTENT_ERROR_UNABLE_TO_LOAD_DEPENDENCY;
		}
	}
	
	if (material == NULL){
		rLog::Error(name + ": unable to load material - %u", m_error);
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
		NotifyAssetUnloaded(rASSET_MATERIAL, name);
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
	for (rContentListenerList::iterator it = m_listeners.begin(); it != m_listeners.end(); ++it){
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

rGeometry* rContentManager::LoadGeometryFromPath(const rString& path, const rString& name){
	rGeometryData geometryData;
	rGeometryDataReader reader;
	reader.ReadFromFile(path, geometryData);

	return LoadGeometry(geometryData, name);
}

rGeometry* rContentManager::LoadGeometry(const rGeometryData& geometryData, const rString& name){
	rGeometry* geometry = NULL;

	if (m_geometry.count(name)){
		m_error = rCONTENT_ERROR_ASSET_NAME_ALREADY_PRESENT;
	}
	else{
		unsigned int vertexBuffer = m_graphicsDevice->CreateArrayBuffer((const char*)geometryData.VertexData(), geometryData.VertexDataSize());
		unsigned int boneLinkBuffer = 0;

		if (geometryData.VertexBoneLinkCount() > 0){
			rVertexBoneDataArray vertexBoneData;
			geometryData.CreateVetexBoneDataArray(vertexBoneData);

			boneLinkBuffer = m_graphicsDevice->CreateArrayBuffer((const char*)&vertexBoneData[0], vertexBoneData.size() * sizeof (rVertexBoneDataArray::value_type));
		}

		geometry = new rGeometry(vertexBuffer, boneLinkBuffer , GetNextAssetId(), name, geometryData.Path());
		
		rArrayString bufferNames;
		geometryData.GetElementBufferNames(bufferNames);
		
		for (size_t i = 0; i < bufferNames.size(); i++){
			rElementBufferData* buffer = geometryData.GetElementBuffer(bufferNames[i]);
			
			unsigned int elementBufferId = m_graphicsDevice->CreateElementBuffer(buffer->GetElementData(), buffer->ElementDataSize());
			geometry->AddElementBuffer(bufferNames[i], elementBufferId, buffer->ElementCount(), buffer->GeometryType());
		}
		
		m_geometry[name] = geometry;
		m_error = rCONTENT_ERROR_NONE;
	}
	
	return geometry;
}

void rContentManager::DeleteGeometryBuffers(rGeometry* geometry){
	m_graphicsDevice->DeleteBuffer(geometry->VertexBufferId());
	
	rArrayString bufferNames;
	const rElementBuffer* elementBuffer = NULL;
	geometry->GetElementBufferNames(bufferNames);
	
	for (size_t i = 0; i < bufferNames.size(); i++){
		elementBuffer = geometry->GetElementBuffer(bufferNames[i]);
		m_graphicsDevice->DeleteBuffer(elementBuffer->BufferId());
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


rFont* rContentManager::GetFontAsset(const rString& name) const{
	rFontMap::const_iterator result = m_fonts.find(name);

	if (result == m_fonts.end()){
		return NULL;
	}
	else {
		return result->second;
	}
}

rFont* rContentManager::LoadFontFromPath(const rString& path, const rString& name){
	rFontData fontData;
	fontData.LoadFontDataFromFile(path);
	return LoadFont(fontData, name);
}

rFont* rContentManager::LoadFont(const rFontData& fontData, const rString& name){
	rFont* font = NULL;
	if (m_fonts.count(name)){
		m_error = rCONTENT_ERROR_ASSET_NAME_ALREADY_PRESENT;
	}
	else{
		rTexture2D* fontTexture = NULL;
		
		if (fontData.TextureDataPresent()){
			fontTexture = LoadTexture(fontData.TextureData(), name + "_texture");
		}
		else{
			fontTexture = GetOrLoadTexture(name + "_texture", fontData.TexturePath());
		}

		font = new rFont(fontTexture, fontData.Size(), fontData.LineHeight(), fontData.Ascender(), fontData.Descender(), GetNextAssetId(), name, fontData.GetPath());
		rGlyphDataArray glyphs;
		fontData.GetGlyphData(glyphs);

		for (size_t i = 0; i < glyphs.size(); i++){
			font->AddGlyph(*glyphs[i]);
		}

		m_fonts[name] = font;
	}


	return font;
}

rContentError rContentManager::RemoveFontAsset(const rString& name){
	return rCONTENT_ERROR_NONE;
}

size_t rContentManager::NumFonts(){
	return m_fonts.size();
}

rModel* rContentManager::GetModelAsset(const rString& name) const{
	rModelMap::const_iterator result = m_models.find(name);

	if (result == m_models.end()){
		return NULL;
	}
	else{
		return result->second;
	}
}

rModel* rContentManager::LoadModel(rModelData& modelData, const rString& name){
	if (m_models.count(name)){
		m_error = rCONTENT_ERROR_ASSET_NAME_ALREADY_PRESENT;
		return NULL;
	}
	else{
		rString modelDir = rPath::Directory(modelData.GetPath());
		rString geometryFile = rPath::Assemble(modelDir, modelData.GetName(), ".rgeo");
		rGeometry* geometry = GetOrLoadGeometry(modelData.GetName(), geometryFile);

		rModel* model = new rModel(geometry, GetNextAssetId(), name, "");
		rArrayString meshNames;
		modelData.GetMeshDataNames(meshNames);

		for (size_t i =0; i < meshNames.size(); i++){
			rMeshData* meshData = modelData.GetMeshData(meshNames[i]);
			rString materialFile = rPath::Assemble(modelDir, meshData->material, ".rmat");
			rMaterial* material = GetOrLoadMaterial(meshData->material, materialFile);

			model->CreateMesh(meshData->name, meshData->buffer, material, meshData->boundingBox);
		}

		rString skeletonFile = rPath::Assemble(modelDir, name, ".rskl");
		rSkeleton* skeleton= GetOrLoadSkeleton(name, skeletonFile);
		if (skeleton)
			model->SetSkeleton(skeleton);

		m_models[name] = model;
		m_error = rCONTENT_ERROR_NONE;
		return model;
	}
}

rModel* rContentManager::LoadModelFromPath(const rString& path, const rString& name){
	rModelDataReader reader;
	rModelData modelData;
	rContentError error = reader.LoadFromFile(path, modelData);

	if (error)
		return NULL;
	else
		return LoadModel(modelData, name);
}

rModel* rContentManager::GetOrLoadModel(const rString& name, const rString& path){
	rModel* model = GetModelAsset(name);

	if (!model){
		model = LoadModelFromPath(path, name);
	}

	return model;
}

rContentError rContentManager::RemoveModelAsset(const rString& name){
	return rCONTENT_ERROR_NONE;
}

size_t rContentManager::NumModels() const{
	return m_models.size();
}

void rContentManager::GetModelNames(rArrayString& names) const{
	names.clear();

	rModelMap::const_iterator end =  m_models.end();
	for (rModelMap::const_iterator it = m_models.begin(); it != end; ++it){
		names.push_back(it->first);
	}
}

rSkeleton* rContentManager::GetSkeletonAsset(const rString& name) const{
	rSkeleton* skeleton = NULL;

	rSkeletonMap::const_iterator result = m_skeletons.find(name);

	if (result != m_skeletons.end())
		skeleton = result->second;

	return skeleton;
}

rSkeleton* rContentManager::LoadSkeletonFromPath(const rString& path, const rString& name){
	rSkeleton* skeleton = new rSkeleton();
	rSkeletonData skeletonData;
	int error = skeletonData.ReadFromFile(path, *skeleton);

	if (error){
		delete skeleton;
		skeleton = NULL;
	}
	else{
		m_skeletons[name] = skeleton;
	}

	return skeleton;
}

rSkeleton* rContentManager::GetOrLoadSkeleton(const rString& name, const rString& path){
	rSkeleton* skeleton = GetSkeletonAsset(name);

	if (!skeleton){
		skeleton = LoadSkeletonFromPath(path, name);
	}

	return skeleton;
}

rAssetStream rContentManager::LoadTextFromPath(const rString& path){
	rIFileStream* fileStream = new rIFileStream(path);
	rAssetStream streamPtr;

	if (fileStream->IsOk())
		streamPtr.reset(fileStream);
	else
		delete fileStream;

	return streamPtr;
}

rContentError rContentManager::RemoveSkeletonAsset(const rString& name){
	return rCONTENT_ERROR_NONE;
}

size_t rContentManager::NumSkeletons(){
	return m_skeletons.size();
}

void rContentManager::NotifyManifestBegin(const rString& path, int total) {
	for (rContentListenerList::iterator it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->BeginManifestLoad(path, total);
}

void rContentManager::NotifyManifestProgress(rAssetType type, const rString& name, const rString& path, int current, int total) {
	for (rContentListenerList::iterator it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->ManifestLoadProgress(type, name, path, current, total);
}

void rContentManager::NotifyManifestLoadError(rAssetType type, const rString& name, const rString& path, rContentError error, int current, int total){
	for (rContentListenerList::iterator it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->ManifestLoadError(type, name, path, error, current, total);
}

void rContentManager::NotifyManifestEnd(const rString& path){
	for (rContentListenerList::iterator it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->EndManifestLoad(path);
}

void rContentManager::NotifyAssetLoadComplete(rAssetType type, const rString& name, const rString& path){
	for (rContentListenerList::iterator it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->AssetLoadComplete(type, name, path);
}

void rContentManager::NotifyAssetLoadError(rAssetType type, const rString& name, const rString& path, rContentError error){
	for (rContentListenerList::iterator it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->AssetLoadError(type, name, path, error);
}

void rContentManager::NotifyAssetUnloaded(rAssetType type, const rString& name){
	for (rContentListenerList::iterator it = m_listeners.begin(); it != m_listeners.end(); ++it)
		(*it)->AssetUnloaded(type, name);
}

bool rContentManager::ProcessingBatchFile() const{
	return m_processingBatchFile;
}
	
void rContentManager::Init() {}
void rContentManager::Uninit() {}
void rContentManager::InitDefaultAssets() {}
