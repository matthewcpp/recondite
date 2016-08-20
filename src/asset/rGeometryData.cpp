#include "asset/rGeometryData.hpp"


namespace recondite {
	struct GeometryData::Impl {
		std::vector<rVector3> vertices;
		std::vector<rVector3> normals;
		std::vector<rVector2> texCoords;
	};

	GeometryData::GeometryData() {
		_impl = new Impl();
	}

	GeometryData::~GeometryData() {
		delete _impl;
	}

	size_t GeometryData::VertexCount() const {
		return _impl->vertices.size();
	}

	char* GeometryData::VertexData() const {
		return (char*)_impl->vertices.data();
	}

	char* GeometryData::NormalData() const {
		return (char*)_impl->normals.data();
	}

	char* GeometryData::TexCoordData() const {
		return (char*)_impl->texCoords.data();
	}

	void GeometryData::AllocateVertices(size_t size) {
		_impl->vertices.resize(size);
	}

	void GeometryData::AllocateTexCoords(size_t size) {
		_impl->texCoords.resize(size);
	}

	void GeometryData::AllocateNormals(size_t size) {
		_impl->normals.resize(size);
	}

	void GeometryData::Clear() {
		_impl->vertices.clear();
		_impl->texCoords.clear();
	}

	void GeometryData::PushVertex(const rVector3& position) {
		_impl->vertices.emplace_back(position);
	}

	void GeometryData::SetVertex(size_t index, const rVector3& position) {
		_impl->vertices[index] = position;
	}

	void GeometryData::GetVertex(size_t index, rVector3& position) {
		position = _impl->vertices[index];
	}

	void GeometryData::PushVertices(rVector3* vertices, size_t count) {
		size_t size = _impl->vertices.size();

		_impl->vertices.resize(size + count);
		memcpy(&_impl->vertices[size], vertices, sizeof(rVector3) * count);
	}

	size_t GeometryData::VertexDataSize() const {
		return _impl->vertices.size() * sizeof(rVector3);
	}

	void GeometryData::PushTexCoord(const rVector2& texCoord) {
		_impl->texCoords.push_back(texCoord);
	}

	void GeometryData::SetTexCoord(size_t index, const rVector2& texCoord) {
		_impl->texCoords[index] = texCoord;
	}

	void GeometryData::GetTextCoord(size_t index, rVector2& texCoord) {
		texCoord = _impl->texCoords[index];
	}

	void GeometryData::PushTexCoords(const rVector2* texCoords, size_t count) {
		size_t size = _impl->texCoords.size();

		_impl->texCoords.resize(size + count);
		memcpy(&_impl->texCoords[size], texCoords, sizeof(rVector2) * count);
	}

	size_t GeometryData::TexCoordDataSize() const {
		return _impl->texCoords.size() * sizeof(rVector2);
	}

	bool GeometryData::HasTexCoords() const {
		return _impl->texCoords.size() > 0;
	}

	void GeometryData::PushNormal(const rVector3& normal) {
		_impl->normals.emplace_back(normal);
	}

	void GeometryData::SetNormal(size_t index, const rVector3& normal) {
		_impl->normals[index] = normal;
	}

	void GeometryData::GetNormal(size_t index, rVector3& normal) {
		normal = _impl->normals[index];
	}

	void GeometryData::PushNormals(const rVector3* normals, size_t count) {
		size_t size = _impl->normals.size();

		_impl->normals.resize(size + count);
		memcpy(&_impl->normals[size], normals, sizeof(rVector3) * count);
	}

	size_t GeometryData::NormalDataSize() const {
		return _impl->normals.size() * sizeof(rVector3);
	}

	bool GeometryData::HasNormals() const {
		return _impl->normals.size() > 0;
	}
}
