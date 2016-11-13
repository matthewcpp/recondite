#include "asset/rModel.hpp"

namespace recondite {

	void Geometry::Reset(uint32_t bufferId, uint32_t vertexCount, bool hasNormals, bool hasTexCoords) {
		_bufferId = bufferId;
		_vertexCount = vertexCount;
		_hasNormals = hasNormals;
		_hasTexCoords = hasTexCoords;
	}

	struct Model::Impl {
		Geometry geometry;
		rString name;
		rAlignedBox3 boundingBox;
		std::vector<std::unique_ptr<Mesh>> triangleMeshes;
		std::vector<std::unique_ptr<Mesh>> lineMeshes;

		std::unique_ptr<Skeleton> skeleton;

		Impl(const rString& n, const Geometry& geo, Skeleton* skel) : name(n), geometry(geo), skeleton(skel){}
	};

	Model::Model(const rString& name, const Geometry& geometry, Skeleton* skeleton) {
		_impl = new Impl(name, geometry, skeleton);
	}

	rString Model::GetName() const {
		return _impl->name;
	}

	Model::~Model() {
		delete _impl;
	}

	const Geometry* Model::GetGeometry() const{
		return &_impl->geometry;
	}

	Mesh* Model::CreateTriangleMesh(uint32_t bufferId, uint32_t bufferSize, rMaterial* material) {
		Mesh* mesh = new Mesh(bufferId, bufferSize, rGeometryType::Triangles, material);
		_impl->triangleMeshes.emplace_back(mesh);

		return mesh;
	}

	size_t Model::GetTriangleMeshCount() const {
		return _impl->triangleMeshes.size();
	}

	Mesh* Model::GetTriangleMesh(size_t index) const{
		return _impl->triangleMeshes[index].get();
	}

	Mesh* Model::CreateLineMesh(uint32_t bufferId, uint32_t bufferSize, rMaterial* material) {
		Mesh* mesh = new Mesh(bufferId, bufferSize, rGeometryType::Lines, material);
		_impl->lineMeshes.emplace_back(mesh);

		return mesh;
	}

	size_t  Model::GetLineMeshCount() const {
		return _impl->lineMeshes.size();
	}

	Mesh* Model::GetLineMesh(size_t index) const {
		return _impl->lineMeshes[index].get();
	}

	rAlignedBox3 Model::GetBoundingBox() const {
		return _impl->boundingBox;
	}

	void Model::SetBoundingBox(const rAlignedBox3& box) {
		_impl->boundingBox = box;
	}

	Skeleton* Model::GetSkeleton() const {
		return _impl->skeleton.get();
	}
}