#include "asset/rModelManager.hpp"

rModelManager::rModelManager(rFileSystem* fileSysytem, rShaderManager* shaderManager, rGeometryManager* geometryManager)
	:rAssetManager < rModel, rModelData, rModelFile >(fileSysytem)
{
	m_geometryManager = geometryManager;
	m_shadermanager = shaderManager;
}

rModel* rModelManager::CreateAssetFromData(const rModelData& modelData, const rString& name){
	rGeometry* geometry = m_geometryManager->LoadFromData(*modelData.GetGeometryData(), name + "::geometry");

	rModel* model = new rModel(name, geometry);

	rArrayString meshDataNames;
	modelData.GetMeshDataNames(meshDataNames);

	for (size_t i = 0; i < meshDataNames.size(); i++){
		rMeshData* meshData = modelData.GetMeshData(meshDataNames[i]);

		rMaterial* material = new rMaterial();// m_materialManager->CreateMaterial(name + "::" + meshData->meshName + "::material");

		rMesh* mesh = model->CreateMesh(meshData->meshName, meshData->elementBufferName, meshData->geometryType, material, meshData->boundingBox);
	}
	return model;
}

void rModelManager::DisposeAsset(rModel* model){

	m_geometryManager->Release(model->Geometry()->Name());
}