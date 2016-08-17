#include "asset/rModelData.hpp"


namespace recondite {
	struct MeshData::Impl {
		rString name;
		rMaterial material;
		std::vector<uint16_t> elements;
		rGeometryType geometryType;
	};

	MeshData::MeshData(rGeometryType geometryType) {
		_impl = new Impl();
		_impl->geometryType = geometryType;
	}

	MeshData::~MeshData() {
		delete _impl;
	}

	rGeometryType MeshData::GetGeometryType() const {
		return _impl->geometryType;
	}

	rString MeshData::GetName() const {
		return _impl->name;
	}

	void MeshData::SetName(const rString& name) {
		_impl->name = name;
	}

	rMaterial& MeshData::GetMaterial() {
		return _impl->material;
	}

	const rMaterial& MeshData::GetMaterial() const {
		return _impl->material;
	}

	const uint16_t* MeshData::GetBufferData() const {
		return _impl->elements.data();
	}

	size_t MeshData::GetElementCount() const {
		return _impl->elements.size();
	}

	void MeshData::Push(uint16_t element) {
		_impl->elements.push_back(element);
	}

	void MeshData::Push(uint16_t element1, uint16_t element2) {
		_impl->elements.push_back(element1);
		_impl->elements.push_back(element2);
	}

	void MeshData::Push(uint16_t element1, uint16_t element2, uint16_t element3) {
		_impl->elements.push_back(element1);
		_impl->elements.push_back(element2);
		_impl->elements.push_back(element3);
	}

	size_t MeshData::GetBufferDataSize() const {
		return _impl->elements.size() * sizeof(uint16_t);
	}


	struct ModelData::Impl {
		GeometryData geometryData;
		std::vector<std::unique_ptr<MeshData>> triangleMeshes;
		std::vector<std::unique_ptr<MeshData>> lineMeshes;
	};

	ModelData::ModelData() {
		_impl = new Impl();
	}

	ModelData::~ModelData() {
		delete _impl;
	}

	void ModelData::Clear() {
		_impl->geometryData.Clear();
		_impl->triangleMeshes.clear();
	}

	MeshData* ModelData::CreateTriangleMesh() {
		MeshData* meshData = new MeshData(rGeometryType::Triangles);
		_impl->triangleMeshes.emplace_back(meshData);
		return meshData;
	}

	size_t ModelData::GetTriangleMeshCount() const {
		return _impl->triangleMeshes.size();
	}

	MeshData*  ModelData::GetTriangleMesh(size_t index) {
		return _impl->triangleMeshes[index].get();
	}

	const MeshData* ModelData::GetTriangleMesh(size_t index) const{
		return _impl->triangleMeshes[index].get();
	}

	GeometryData* ModelData::GetGeometryData() {
		return &_impl->geometryData;
	}

	const GeometryData* ModelData::GetGeometryData() const {
		return &_impl->geometryData;
	}

	MeshData* ModelData::CreateLineMesh() {
		MeshData* meshData = new MeshData(rGeometryType::Lines);
		_impl->lineMeshes.emplace_back(meshData);
		return meshData;
	}

	size_t ModelData::GetLineMeshCount() const {
		return _impl->lineMeshes.size();
	}

	MeshData* ModelData::GetLineMesh(size_t index) const {
		return _impl->lineMeshes[index].get();
	}
}