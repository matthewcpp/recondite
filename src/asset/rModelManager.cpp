#include "asset/rModelManager.hpp"

struct rModelManager::Impl{
	Impl(rFileSystem* fs, rGraphicsDevice* gd) : fileSysytem(fs), graphicsDevice(gd){}

	rGeometry* CreateGeometry(rGeometryData* geometryData);

	rFileSystem* fileSysytem;
	rGraphicsDevice* graphicsDevice;
};


rModelManager::rModelManager(rFileSystem* fileSysytem, rGraphicsDevice* graphicsDevice){
	_impl = new Impl(fileSysytem, graphicsDevice);
}

rModelManager::~rModelManager(){
	delete _impl;
}

void rModelManager::Clear(){
}

rGeometry* rModelManager::Impl::CreateGeometry(rGeometryData* geometryData){
	unsigned int vertexBuffer = graphicsDevice->CreateArrayBuffer((const char*)geometryData->VertexData(), geometryData->VertexDataSize());

	rGeometry* geometry = new rGeometry("", geometryData->GeometryProfile(), vertexBuffer, 0);

	//TODO: use foreach interface?
	rArrayString bufferNames;
	geometryData->GetElementBufferNames(bufferNames);

	for (size_t i = 0; i < bufferNames.size(); i++){
		rElementBufferData* buffer = geometryData->GetElementBuffer(bufferNames[i]);

		unsigned int elementBufferId = graphicsDevice->CreateElementBuffer(buffer->GetElementData(), buffer->ElementDataSize());
		geometry->AddElementBuffer(bufferNames[i], elementBufferId, buffer->ElementCount(), buffer->GeometryType());
	}

	return geometry;
}

rModel* rModelManager::LoadFromData(const rModelData& modelData, const rString& name){
	rGeometry* geometry = _impl->CreateGeometry(modelData.GetGeometryData());
	rModel* model = new rModel(name, geometry);

	rArrayString meshDataNames;
	modelData.GetMeshDataNames(meshDataNames);

		for (size_t i = 0; i < meshDataNames.size(); i++){
			rMeshData* meshData = modelData.GetMeshData(meshDataNames[i]);

			rMaterial* material = new rMaterial();
			rMesh* mesh = model->CreateMesh(meshData->meshName, meshData->elementBufferName, meshData->geometryType, material, meshData->boundingBox);
		}

	return model;
}

int rModelManager::Delete(const rString& name){
	return 0;
}