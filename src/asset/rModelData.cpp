#include "asset/rModelData.hpp"


namespace recondite {
	struct MeshData::Impl {
		rString name;
		uint32_t materialId;
		std::vector<uint16_t> elements;
		rGeometryType geometryType;
		rAlignedBox3 boundingBox;
		rMaterial* material;
	};

	MeshData::MeshData(rGeometryType geometryType) {
		_impl = new Impl();
		_impl->geometryType = geometryType;
		_impl->boundingBox.Empty();
		_impl->materialId = UINT32_MAX;
		_impl->material = nullptr;
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

	uint32_t MeshData::GetMaterialDataId() const{
		return _impl->materialId;
	}

	void MeshData::SetMaterialDataId(uint32_t id) {
		_impl->materialId = id;
	}

	void MeshData::SetMaterial(rMaterial* material) {
		_impl->material = material;
	}

	rMaterial* MeshData::GetMaterial() const {
		return _impl->material;
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

		std::unique_ptr<Skeleton> skeleton;

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
		_impl->lineMeshes.clear();
		_impl->textures.clear();
		_impl->materials.clear();

		_impl->skeleton.reset(nullptr);
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

	void ModelData::DeleteLastTexture() {
		_impl->textures.pop_back();
	}

	size_t ModelData::GetNumTextures() const {
		return _impl->textures.size();
	}

	rTextureData* ModelData::GetTexture(size_t index) const{
		return _impl->textures[index].get();
	}

	MaterialData* ModelData::CreateMaterial() {
		MaterialData* material = new MaterialData(_impl->materials.size());
		_impl->materials.emplace_back(material);
		return material;
	}

	size_t ModelData::GetNumMaterials() const {
		return _impl->materials.size();
	}

	MaterialData* ModelData::GetMaterial(size_t index) const{
		return _impl->materials[index].get();
	}

	Skeleton* ModelData::CreateSkeleton() {
		_impl->skeleton.reset(new Skeleton());
		return _impl->skeleton.get();
	}

	Skeleton* ModelData::GetSkeleton() const {
		return _impl->skeleton.get();
	}

	Skeleton* ModelData::DetachSkeleton() {
		return _impl->skeleton.release();
	}

	const uint32_t MagicNumber = 1984; //rmdl
	const uint32_t CurrentVersion = 1;

	struct ModelFileHeader {
		uint32_t magicNumber;
		uint32_t version;
		uint32_t numTextures;
		uint32_t numMaterials;
		uint32_t numVertices;
		uint32_t triangleMeshCount;
		uint32_t lineMeshCount;
		uint32_t animated;
	};

	void ReadMesh(MeshData* meshData, rIStream& stream) {
		uint32_t elementCount;
		stream.Read((char*)&elementCount, sizeof(uint32_t));
		meshData->AllocateBuffer(elementCount);
		stream.Read(meshData->GetBufferData(), meshData->GetBufferDataSize());

		rAlignedBox3 boundingBox;
		stream.Read((char*)&boundingBox, sizeof(rAlignedBox3));

		uint32_t materialId;
		stream.Read((char*)&materialId, sizeof(uint32_t));
		meshData->SetMaterialDataId(materialId);

		uint32_t nameLength;
		stream.Read((char*)&nameLength, sizeof(uint32_t));

		if (nameLength > 0) {
			std::vector<char> nameBuffer(nameLength);
			stream.Read(nameBuffer.data(), nameLength);
			rString nameStr(nameBuffer.data(), nameLength);
			meshData->SetName(nameStr);
		}
	}

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

			stream.Read((char*)&_impl->boundingBox, sizeof(rAlignedBox3));

			for (size_t i = 0; i < header.triangleMeshCount; i++) {
				MeshData* meshData = CreateTriangleMesh();
				ReadMesh(meshData, stream);
			}

			for (size_t i = 0; i < header.lineMeshCount; i++) {
				MeshData* meshData = CreateLineMesh();
				ReadMesh(meshData, stream);
			}

			_impl->geometryData.Read(stream);

			if (header.animated)
				CreateSkeleton()->Read(stream);

			return 0;
		}
		else {
			return 1;
		}
	}

	void WriteMesh(const MeshData* meshData, rOStream& stream) {
		uint32_t elementCount = meshData->GetElementCount();

		stream.Write((const char*)&elementCount, sizeof(uint32_t));
		stream.Write(meshData->GetBufferData(), meshData->GetBufferDataSize());

		rAlignedBox3 boundingBox = meshData->GetBoundingBox();
		stream.Write((const char*)&boundingBox, sizeof(rAlignedBox3));

		uint32_t materialIndex = meshData->GetMaterialDataId();
		stream.Write((const char*)&materialIndex, sizeof(uint32_t));

		rString meshName = meshData->GetName();
		uint32_t nameLength = meshName.size();
		stream.Write((const char*)&nameLength, sizeof(uint32_t));

		if (nameLength > 0) {
			stream.Write(meshName.c_str(), nameLength);
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

		stream.Write((const char*)&_impl->boundingBox, sizeof(rAlignedBox3));

		for (size_t i = 0; i < _impl->triangleMeshes.size(); i++) {
			MeshData* meshData = _impl->triangleMeshes[i].get();
			WriteMesh(meshData, stream);
		}

		for (size_t i = 0; i < _impl->lineMeshes.size(); i++) {
			MeshData* meshData = _impl->lineMeshes[i].get();
			WriteMesh(meshData, stream);
		}

		_impl->geometryData.Write(stream);

		if (header.animated)
			_impl->skeleton->Write(stream);

		return 0;
	}

	void ModelData::Impl::InitHeader(ModelFileHeader& header) {
		header.magicNumber = MagicNumber;
		header.version = CurrentVersion;

		header.numVertices = geometryData.VertexCount();

		header.triangleMeshCount = triangleMeshes.size();
		header.lineMeshCount = lineMeshes.size();

		header.numTextures = textures.size();
		header.numMaterials = materials.size();

		header.animated = skeleton.get() ? 1 : 0;
	}
}