#include "asset/rModelManager.hpp"

rModelManager::rModelManager(rFileSystem* fileSysytem, rMaterialManager* materialManager, rShaderManager* shaderManager, rGeometryManager* geometryManager)
	:rAssetManager < rModel, rModelData, rModelFile >(fileSysytem)
{
	m_materialManager = materialManager;
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

		rMaterial* material = m_materialManager->CreateMaterial(name + "::" + meshData->meshName + "::material");

		if (meshData->geometryType == rGeometryType::Lines || meshData->geometryType == rGeometryType::LineLoop)
			material->SetShader(m_shadermanager->DefaultLineShader());
		else
			material->SetShader(m_shadermanager->DefaultLineShader());

		rMesh* mesh = model->CreateMesh(meshData->meshName, meshData->elementBufferName, meshData->geometryType, material, meshData->boundingBox);
	}
	return model;
}

void rModelManager::DisposeAsset(rModel* model){
	rMaterialManager* materialManager = m_materialManager;

	model->ForEach([materialManager](rMesh* mesh)->bool{
		materialManager->Release(mesh->Material()->Name());
		return true;
	});

	m_geometryManager->Release(model->Geometry()->Name());
}