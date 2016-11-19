#include "asset/rGeometryData.hpp"

#include "rDefs.hpp"

namespace recondite {
	struct GeometryDataHeader {
		uint32_t vertexCount;
		uint32_t hasTexCoords;
		uint32_t hasVertexBoneWeights;
	};

	struct GeometryData::Impl {
		std::vector<rVector3> vertices;
		std::vector<rVector3> normals;
		std::vector<rVector2> texCoords;

		std::vector<uint32_t> vertexBoneIndices;
		std::vector<float> vertexBoneWeights;

		void InitHeader(GeometryDataHeader& header);
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

	bool GeometryData::HasVertexBoneWeights() const {
		return _impl->vertexBoneWeights.size() > 0;
	}

	void GeometryData::AllocateVertexWeightData(size_t numVertices) {
		_impl->vertexBoneIndices.resize(_impl->vertexBoneIndices.size() + (numVertices * rMAX_BONE_WEIGHTS_PER_VERTEX), 0);
		_impl->vertexBoneWeights.resize(_impl->vertexBoneWeights.size() + (numVertices * rMAX_BONE_WEIGHTS_PER_VERTEX), 0.0);
	}

	bool GeometryData::AddVertexWeight(size_t vertexIndex, size_t boneIndex, float weight) {
		size_t arrayIndex = vertexIndex * rMAX_BONE_WEIGHTS_PER_VERTEX;

		for (size_t i = 0; i < rMAX_BONE_WEIGHTS_PER_VERTEX; i++) {
			if (_impl->vertexBoneWeights[arrayIndex + i] == 0.0f) {
				_impl->vertexBoneIndices[arrayIndex + i] = boneIndex;
				_impl->vertexBoneWeights[arrayIndex + i] = weight;

				return true;
			}
		}

		return false;
	}

	size_t GeometryData::VertexBoneWeightsDataSize() const {
		return _impl->vertexBoneWeights.size() * sizeof(float);
	}

	const char* GeometryData::VertexBoneWeightData() const {
		return (const char*)_impl->vertexBoneWeights.data();
	}

	size_t GeometryData::VertexBoneIndicesDataSize() const {
		return _impl->vertexBoneIndices.size() * sizeof(uint32_t);
	}

	const char* GeometryData::VertexBoneIndicesData() const {
		return (const char*)_impl->vertexBoneIndices.data();
	}

	int GeometryData::Read(rIStream& stream) {
		GeometryDataHeader header;
		stream.Read((char*)&header, sizeof(GeometryDataHeader));

		if (header.vertexCount > 0) {
			_impl->vertices.resize(header.vertexCount);
			_impl->normals.resize(header.vertexCount);

			stream.Read((char*)_impl->vertices.data(), header.vertexCount * sizeof(rVector3));
			stream.Read((char*)_impl->normals.data(), header.vertexCount * sizeof(rVector3));
		}

		if (header.hasTexCoords) {
			_impl->texCoords.resize(header.vertexCount);
			stream.Read((char*)_impl->texCoords.data(), header.vertexCount * sizeof(rVector2));
		}

		if (header.hasVertexBoneWeights) {
			_impl->vertexBoneIndices.resize(header.vertexCount * rMAX_BONE_WEIGHTS_PER_VERTEX);
			_impl->vertexBoneWeights.resize(header.vertexCount * rMAX_BONE_WEIGHTS_PER_VERTEX);

			stream.Read((char*)_impl->vertexBoneIndices.data(), sizeof(uint32_t) * header.vertexCount * rMAX_BONE_WEIGHTS_PER_VERTEX);
			stream.Read((char*)_impl->vertexBoneWeights.data(), sizeof(float) * header.vertexCount * rMAX_BONE_WEIGHTS_PER_VERTEX);
		}

		return 0;
	}

	void GeometryData::Impl::InitHeader(GeometryDataHeader& header) {
		header.vertexCount = vertices.size();
		header.hasTexCoords = texCoords.size() > 0;
		header.hasVertexBoneWeights = vertexBoneWeights.size() > 0;
		
	}

	int GeometryData::Write(rOStream& stream) {
		GeometryDataHeader header;
		_impl->InitHeader(header);
		stream.Write((const char*)&header, sizeof(GeometryDataHeader));

		if (_impl->vertices.size() > 0) {
			stream.Write((const char*)_impl->vertices.data(), _impl->vertices.size() * sizeof(rVector3));
			stream.Write((const char*)_impl->normals.data(), _impl->normals.size() * sizeof(rVector3));
		}

		if (_impl->texCoords.size() > 0) {
			stream.Write((const char*)_impl->texCoords.data(), _impl->texCoords.size() * sizeof(rVector2));
		}

		if (_impl->vertexBoneIndices.size() > 0) {
			stream.Write((const char*)_impl->vertexBoneIndices.data(), _impl->vertexBoneIndices.size() * sizeof(uint32_t));
			stream.Write((const char*)_impl->vertexBoneWeights.data(), _impl->vertexBoneWeights.size() * sizeof(float));
		}

		return 0;
	}
}
