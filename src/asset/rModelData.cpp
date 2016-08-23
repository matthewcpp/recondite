#include "asset/rModelData.hpp"


namespace recondite {
	struct MeshData::Impl {
		rString name;
		uint32_t materialId;
		std::vector<uint16_t> elements;
		rGeometryType geometryType;
		rAlignedBox3 boundingBox;
	};

	MeshData::MeshData(rGeometryType geometryType) {
		_impl = new Impl();
		_impl->geometryType = geometryType;
		_impl->boundingBox.Empty();
		_impl->materialId = UINT32_MAX;
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

	uint32_t MeshData::GetMaterialId() const{
		return _impl->materialId;
	}

	void MeshData::SetMaterialId(uint32_t id) {
		_impl->materialId = id;
	}

	char* MeshData::GetBufferData() const {
		return (char*)_impl->elements.data();
	}

	void MeshData::AllocateBuffer(size_t size) {
		_impl->elements.resize(size);
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

	rAlignedBox3 MeshData::GetBoundingBox() const {
		return _impl->boundingBox;
	}

	void MeshData::SetBoundingBox(const rAlignedBox3& box) {
		_impl->boundingBox = box;
	}

	struct ModelFileHeader;

	struct ModelData::Impl {
		GeometryData geometryData;
		rAlignedBox3 boundingBox;

		typedef std::vector<std::unique_ptr<MeshData>> MeshDataRefArray;

		MeshDataRefArray triangleMeshes;
		MeshDataRefArray lineMeshes;

		std::vector<std::unique_ptr<rTextureData>> textures;
		std::vector<std::unique_ptr<MaterialData>> materials;

		void CalculateMeshBounding(MeshDataRefArray& refArray);
		void InitHeader(ModelFileHeader& header);
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

	rAlignedBox3 ModelData::GetBoundingBox() const {
		return _impl->boundingBox;
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

	void ModelData::Impl::CalculateMeshBounding(MeshDataRefArray& refArray) {
		rVector3 point;

		for (size_t i = 0; i < refArray.size(); i++) {
			rAlignedBox3 meshBounding;
			MeshData* meshData = refArray[i].get();

			const uint16_t* elements = (const uint16_t*)meshData->GetBufferData();

			for (size_t e = 0; e < meshData->GetElementCount(); e++) {
				geometryData.GetVertex(elements[e], point);
				meshBounding.AddPoint(point);
			}

			if (meshBounding.IsValid()) {
				meshData->SetBoundingBox(meshBounding);
				boundingBox.AddBox(meshBounding);
			}
		}
	}

	void ModelData::CalculateBoundings() {
		_impl->CalculateMeshBounding(_impl->triangleMeshes);
		_impl->CalculateMeshBounding(_impl->lineMeshes);
	}

	rTextureData* ModelData::CreateTexture() {
		rTextureData* textureData = new rTextureData();
		_impl->textures.emplace_back(textureData);

		return textureData;
	}

	size_t ModelData::GetNumTextures() const {
		return _impl->textures.size();
	}

	rTextureData* ModelData::GetTexture(size_t index) const{
		return _impl->textures[index].get();
	}

	MaterialData* ModelData::CreateMaterial() {
		MaterialData* material = new MaterialData();
		_impl->materials.emplace_back(material);
		return material;
	}

	size_t ModelData::GetNumMaterials() const {
		return _impl->materials.size();
	}

	MaterialData* ModelData::GetMaterial(size_t index) const{
		return _impl->materials[index].get();
	}

	const uint32_t MagicNumber = 1984; //rmdl
	const uint32_t CurrentVersion = 1;

	struct ModelFileHeader {
		uint32_t magicNumber;
		uint32_t version;
		uint32_t numTextures;
		uint32_t numMaterials;
		uint32_t numVertices;
		uint32_t numNormals;
		uint32_t numTexCoords;
		uint32_t triangleMeshCount;
	};

	int ModelData::Read(rIStream& stream) {
		if (stream.IsOk()) {
			ModelFileHeader header;
			stream.Read((char*)&header, sizeof(ModelFileHeader));

			for (size_t i = 0; i < header.numTextures; i++) {
				rTextureData* textureData = new rTextureData();
				textureData->Read(stream);
				_impl->textures.emplace_back(textureData);
			}

			for (size_t i = 0; i < header.numMaterials; i++) {
				MaterialData* materialData = CreateMaterial();
				stream.Read((char*)materialData, sizeof(MaterialData));
			}

			_impl->geometryData.AllocateVertices(header.numVertices);
			stream.Read(_impl->geometryData.VertexData(), _impl->geometryData.VertexDataSize());

			_impl->geometryData.AllocateNormals(header.numNormals);
			stream.Read(_impl->geometryData.NormalData(), _impl->geometryData.NormalDataSize());

			if (header.numTexCoords > 0) {
				_impl->geometryData.AllocateTexCoords(header.numTexCoords);
				stream.Read(_impl->geometryData.TexCoordData(), _impl->geometryData.TexCoordDataSize());
			}

			stream.Read((char*)&_impl->boundingBox, sizeof(rAlignedBox3));

			for (size_t i = 0; i < header.triangleMeshCount; i++) {
				MeshData* meshData = CreateTriangleMesh();

				uint32_t elementCount;
				stream.Read((char*)&elementCount, sizeof(uint32_t));
				meshData->AllocateBuffer(elementCount);
				stream.Read(meshData->GetBufferData(), meshData->GetBufferDataSize());

				rAlignedBox3 boundingBox;
				stream.Read((char*)&boundingBox, sizeof(rAlignedBox3));

				uint32_t materialId;
				stream.Read((char*)&materialId, sizeof(uint32_t));
				meshData->SetMaterialId(materialId);
			}

			return 0;
		}
		else {
			return 1;
		}
	}

	int ModelData::Write(rOStream& stream) {
		ModelFileHeader header;

		_impl->InitHeader(header);
		stream.Write((const char*)&header, sizeof(header));

		for (size_t i = 0; i < _impl->textures.size(); i++) {
			_impl->textures[i]->Write(stream);
		}

		for (size_t i = 0; i < _impl->materials.size(); i++) {
			stream.Write((const char*)_impl->materials[i].get(), sizeof(MaterialData));
		}

		stream.Write(_impl->geometryData.VertexData(), _impl->geometryData.VertexDataSize());
		stream.Write(_impl->geometryData.NormalData(), _impl->geometryData.NormalDataSize());

		if (_impl->geometryData.HasTexCoords())
			stream.Write(_impl->geometryData.TexCoordData(), _impl->geometryData.TexCoordDataSize());

		stream.Write((const char*)&_impl->boundingBox, sizeof(rAlignedBox3));

		for (size_t i = 0; i < _impl->triangleMeshes.size(); i++) {
			MeshData* meshData = _impl->triangleMeshes[i].get();
			uint32_t faceElementCount = meshData->GetElementCount();

			stream.Write((const char*)&faceElementCount, sizeof(uint32_t));
			stream.Write(meshData->GetBufferData(), meshData->GetBufferDataSize());

			rAlignedBox3 boundingBox = meshData->GetBoundingBox();
			stream.Write((const char*)&boundingBox, sizeof(rAlignedBox3));

			uint32_t materialIndex = meshData->GetMaterialId();
			stream.Write((const char*)&materialIndex, sizeof(uint32_t));
		}

		return 0;
	}

	void ModelData::Impl::InitHeader(ModelFileHeader& header) {
		header.magicNumber = MagicNumber;
		header.version = CurrentVersion;

		header.numVertices = geometryData.VertexCount();
		header.numNormals = geometryData.VertexCount();
		header.numTexCoords = geometryData.HasTexCoords() ? geometryData.VertexCount() : 0;

		header.triangleMeshCount = triangleMeshes.size();

		header.numTextures = textures.size();
		header.numMaterials = materials.size();
	}
}