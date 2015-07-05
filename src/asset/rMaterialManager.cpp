#include "asset/rMaterialManager.hpp"

rMaterialManager::rMaterialManager(rFileSystem* fileSystem, rTextureManager* textureManager, rShaderManager* shaderManager)
	:rAssetManager < rMaterial, rMaterialData, rMaterialFile >(fileSystem)
{
	m_shaderManager = shaderManager;
	m_textureManager = textureManager;
}

rMaterial* rMaterialManager::CreateAssetFromData(const rMaterialData& materialData, const rString& name) {
	rMaterial* material = new rMaterial(name);

	material->SetDiffuseColor(materialData.DiffuseColor());

	return material;
}

void rMaterialManager::DisposeAsset(rMaterial* material){
	//release shader here
}

rMaterial* rMaterialManager::CreateMaterial(const rString& name){
	rMaterial* material = Get(name);

	if (!material){
		material = new rMaterial(name);
		AddAsset(name, material);
		return material;
	}
	else{
		return nullptr;
	}
}