#include "asset/rModelManager.hpp"

struct rModelManager::Impl{
	Impl(rFileSystem* fs, rGraphicsDevice* gd) : fileSysytem(fs), graphicsDevice(gd){}

	rFileSystem* fileSysytem;
	rGraphicsDevice* graphicsDevice;
	std::map<rString, std::unique_ptr<Model>> models;

	void DeleteModelData(Model* model);
};


rModelManager::rModelManager(rFileSystem* fileSysytem, rGraphicsDevice* graphicsDevice){
	_impl = new Impl(fileSysytem, graphicsDevice);
}

rModelManager::~rModelManager(){
	delete _impl;
}

Model* rModelManager::LoadFromData(const ModelData& modelData, const rString& name) {
	if (_impl->models.count(name)) return nullptr;


	const GeometryData* geometryData = modelData.GetGeometryData();
	uint32_t bufferId = _impl->graphicsDevice->CreateGeometryBuffer(geometryData);
	Geometry geometry(bufferId, geometryData->VertexCount(), geometryData->HasNormals(), geometryData->HasTexCoords());

	Model* model = new Model(name, geometry);
	model->SetBoundingBox(modelData.GetBoundingBox());

	for (size_t i = 0; i < modelData.GetTriangleMeshCount(); i++) {
		const MeshData* meshData = modelData.GetTriangleMesh(i);

		uint32_t bufferId = _impl->graphicsDevice->CreateElementBuffer(meshData->GetBufferData(), meshData->GetBufferDataSize());
		rMaterial* material = new rMaterial();
		material->Copy(meshData->GetMaterial());
		Mesh* mesh = model->CreateTriangleMesh(bufferId, meshData->GetElementCount(), material);
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
}

void rModelManager::Clear(){
	auto end = _impl->models.end();

	for (auto it = _impl->models.begin(); it != end; ++it) {
		_impl->DeleteModelData(it->second.get());
	}

	_impl->models.clear();
}