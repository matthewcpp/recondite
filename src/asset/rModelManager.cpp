#include "asset/rModelManager.hpp"

#include "stream/rOStringStream.hpp"

struct rModelManager::Impl{
	Impl(rFileSystem* fs, iResourceManager* rm, rGraphicsDevice* gd, rTextureManager* tm)
		: fileSysytem(fs), resourceManager(rm), graphicsDevice(gd), textureManager(tm) {}

	rFileSystem* fileSysytem;
	rGraphicsDevice* graphicsDevice;
	rTextureManager* textureManager;
	iResourceManager* resourceManager;
	std::map<rString, std::unique_ptr<Model>> models;

	void DeleteModelData(Model* model);
	void CreateMaterialsForModel(const ModelData& modelData, const rString& baseName, std::vector<rMaterial*>& materials);
};


rModelManager::rModelManager(rFileSystem* fileSysytem, iResourceManager* resourceManager, rGraphicsDevice* graphicsDevice, rTextureManager* textureManager){
	_impl = new Impl(fileSysytem, resourceManager, graphicsDevice, textureManager);
}

rModelManager::~rModelManager(){
	delete _impl;
}

Model* rModelManager::Get(const rString& name) {
	auto result = _impl->models.find(name);

	if (result == _impl->models.end())
		return nullptr;
	else
		return result->second.get();
}



void rModelManager::Impl::CreateMaterialsForModel(const ModelData& modelData, const rString& baseName, std::vector<rMaterial*>& materials) {
	std::vector<rTexture*> textures;

	for (size_t i = 0; i < modelData.GetNumTextures(); i++) {
		rOStringStream textureName;
		textureName << baseName << "::texture_" << i;

		rTexture* texture = textureManager->Load(*modelData.GetTexture(i), textureName.Str());
		textures.push_back(texture);
	}

	for (size_t i = 0; i < modelData.GetNumMaterials(); i++) {
		MaterialData* materialData = modelData.GetMaterial(i);

		rMaterial* material = new rMaterial();
		material->SetDiffuseColor(materialData->diffuseColor);

		if (materialData->diffuseTextureId != UINT32_MAX) {
			material->SetDiffuseTexture(textures[materialData->diffuseTextureId]);
		}
		
		materials.push_back(material);
	}
}

Model* rModelManager::LoadFromResource(const rString& handle, const rString& name) {
	rIStream* stream = _impl->resourceManager->Open(handle);
	Model* result = nullptr;

	if (stream) {
		ModelData modelData;
		int error = modelData.Read(*stream);

		if (!error) {
			result = LoadFromData(modelData, name);
		}

		_impl->resourceManager->Close(stream);
	}

	return result;
}

Model* rModelManager::LoadFromData(ModelData& modelData, const rString& name) {
	if (_impl->models.count(name)) return nullptr;

	std::vector<rMaterial*> materials;
	_impl->CreateMaterialsForModel(modelData, name, materials);

	Geometry geometry;

	const GeometryData* geometryData = modelData.GetGeometryData();
	if (geometryData->VertexCount()) {
		uint32_t geometryBufferId = _impl->graphicsDevice->CreateGeometryBuffer(geometryData);
		geometry.Reset(geometryBufferId, geometryData->VertexCount(), geometryData->HasNormals(), geometryData->HasTexCoords(), geometryData->HasVertexBoneWeights());
	}

	Model* model = new Model(name, geometry, modelData.DetachSkeleton());
	model->SetBoundingBox(modelData.GetBoundingBox());

	for (size_t i = 0; i < modelData.GetTriangleMeshCount(); i++) {
		const MeshData* meshData = modelData.GetTriangleMesh(i);

		uint32_t bufferId = _impl->graphicsDevice->CreateElementBuffer(meshData->GetBufferData(), meshData->GetBufferDataSize());

		rMaterial* material = meshData->GetMaterial();
		if (!material) {
			uint32_t materialId = meshData->GetMaterialDataId();
			if (materialId == UINT32_MAX)
				material = new rMaterial();
			else
				material = materials[materialId];
		}

		Mesh* mesh = model->CreateTriangleMesh(bufferId, meshData->GetElementCount(), material);
		mesh->SetName(meshData->GetName());
		mesh->SetBoundingBox(meshData->GetBoundingBox());
	}

	for (size_t i = 0; i < modelData.GetLineMeshCount(); i++) {
		const MeshData* meshData = modelData.GetLineMesh(i);

		uint32_t bufferId = _impl->graphicsDevice->CreateElementBuffer(meshData->GetBufferData(), meshData->GetBufferDataSize());
		
		rMaterial* material = meshData->GetMaterial();
		if (!material) {
			uint32_t materialId = meshData->GetMaterialDataId();
			if (materialId == UINT32_MAX)
				material = new rMaterial();
			else
				material = materials[materialId];
		}
		
		Mesh* mesh = model->CreateLineMesh(bufferId, meshData->GetElementCount(), material);
		mesh->SetName(meshData->GetName());
		mesh->SetBoundingBox(meshData->GetBoundingBox());
	}

	_impl->models.emplace(name, model);

	return model;
}

bool rModelManager::Delete(const rString& name) {
	auto result = _impl->models.find(name);

	if (result == _impl->models.end()) {
		return false;
	}
	else {
		Model* model = result->second.get();
		_impl->DeleteModelData(model);
		_impl->models.erase(result);
		return true;
	}
}

void rModelManager::Impl::DeleteModelData(Model* model) {
	graphicsDevice->DeleteBuffer(model->GetGeometry()->GetBufferId());

	for (size_t i = 0; i < model->GetTriangleMeshCount(); i++) {
		graphicsDevice->DeleteBuffer(model->GetTriangleMesh(i)->GetElementBufferId());
	}

	for (size_t i = 0; i < model->GetLineMeshCount(); i++) {
		graphicsDevice->DeleteBuffer(model->GetLineMesh(i)->GetElementBufferId());
	}
}

void rModelManager::Clear(){
	auto end = _impl->models.end();

	for (auto it = _impl->models.begin(); it != end; ++it) {
		_impl->DeleteModelData(it->second.get());
	}

	_impl->models.clear();
}