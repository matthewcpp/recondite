#include "rContentManager.hpp"

rContentManager::rContentManager(rGraphicsDevice* graphicsDevice){
	m_graphicsDevice = graphicsDevice;
	m_nextAssetId = 0;
	
	m_error = rCONTENT_ERROR_NONE;
}

rContentManager::~rContentManager(){
	UnloadAssets();
}

void rContentManager::UnloadAssets(){
	void UnloadMaterials();
	void UnloadShaders();
	void UnloadTextures();
	
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
	
	if (!m_error){
		unsigned int textureId = m_graphicsDevice->CreateTexture(textureData.GetWidth(), textureData.GetHeight(), textureData.GetBPP(), textureData.GetData());
		texture = new rTexture2D(textureData.GetWidth(), textureData.GetHeight(), textureId,
						GetNextAssetId(), name, textureData.GetPath());
	
		rTextureMapEntry entry(name, texture);
		m_textures.insert(entry);
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
	
	if (!m_error){
		unsigned int shaderId = m_graphicsDevice->CreateShaderProgram(shaderData.GetVertexProgram(), shaderData.GetFragmentProgram());
	
		if (shaderId != 0){
			shader = new rShader(shaderId, GetNextAssetId(), name, shaderData.GetPath());
			rShadermapEntry entry(name, shader);
			m_shaders.insert(entry);
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

bool rContentManager::LoadTexturesForMaterial(const rMaterialData& materialData, rMaterial* material){
	rArrayString texParams;
	rMaterialParameterData paramData;
	
	materialData.GetParameterNamesForType(texParams, rMATERIAL_PARAMETER_TEXTURE2D);
	
	for (size_t i = 0; i < texParams.size(); i++){
		materialData.GetParameterData(texParams[i], paramData);
		
		rTexture2D* texture = GetOrLoadTexture(paramData.value, paramData.path);
		if (texture){
			texture->Retain();
			material->SetTexture(texParams[i], texture);
		}
		else{ //missing texture, cannot create material, release previous textures and abort loading process
			for (size_t j = i-1; j >= 0; j--){
				rTexture2D* texture = GetTextureAsset(texParams[j]);
				if (texture) ReleaseAsset(texture);
			}
			
			return false;
		}
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
	
	if (!m_error){
		rShader* shader = GetOrLoadShader(materialData.GetShaderName(), materialData.GetShaderPath());
		
		if (!shader){
			m_error = rCONTENT_ERROR_UNABLE_TO_LOAD_DEPENDENCY;
			return NULL;
		}
		
		shader->Retain();
		material = new rMaterial(shader, GetNextAssetId(), name, materialData.GetPath());
		
		if (LoadTexturesForMaterial(materialData, material)){
			rMaterialMapEntry entry(name, material);
			m_materials.insert(entry);
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
		rArrayString textures;
		material->GetParameterNamesForType(textures, rMATERIAL_PARAMETER_TEXTURE2D);
		
		for (size_t i = 0; i < textures.size(); i++)
			ReleaseAsset(material->GetTexture(textures[i]));
			
		delete material;
		m_error = rCONTENT_ERROR_NONE;
	}
	
	return m_error;
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
void rContentManager::Init() {}
void rContentManager::Uninit() {}
void rContentManager::InitDefaultAssets() {}
