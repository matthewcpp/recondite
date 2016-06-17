#include "asset/rModelData.hpp"

rModelData::rModelData(rGeometryProfile geometryProfile){
	InitWithProfile(geometryProfile);
}

rModelData::rModelData(){
	InitWithProfile(rGeometryProfile::TexCoord);
}

void rModelData::InitWithProfile(rGeometryProfile geometryProfile){
	switch (geometryProfile){
		case rGeometryProfile::TexCoord:
			m_geometryData.reset(new rTexCoordGeometryData());
			break;

		case rGeometryProfile::Primitive:
			m_geometryData.reset(new rPrimitiveGeometryData());
			break;
	}
}

rGeometryData* rModelData::GetGeometryData() const{
	return m_geometryData.get();
}

void rModelData::CreateMeshDataFromGeometry(){
	m_meshes.clear();

	rArrayString elementBuffers;
	m_geometryData->GetElementBufferNames(elementBuffers);

	for (size_t i = 0; i < elementBuffers.size(); i++){
		rString& elementBuffer = elementBuffers[i];
		rElementBufferData* elementBufferData = m_geometryData->GetElementBuffer(elementBuffer);

		if (m_meshes.count(elementBuffer) == 0){
			rMeshData* meshData = new rMeshData(elementBuffer, elementBuffer, elementBufferData->GeometryType());
			m_meshes[elementBuffer].reset(meshData);
		}
	}

	RecalculateMeshBoundingBoxes();
}

void rModelData::RecalculateMeshBoundingBoxes(){
	for (auto& entry : m_meshes){
		RecalulateMeshDataBounding(entry.second.get());
	}
}

void rModelData::RecalulateMeshDataBounding(rMeshData* meshData){
	rElementBufferData* elementBufferData = m_geometryData->GetElementBuffer(meshData->elementBufferName);

	if (elementBufferData){
		meshData->boundingBox.Invalidate();
		rVector3 position;

		const rIndexArray& indices = elementBufferData->GetIndices();
		for (size_t i = 0; i < indices.size(); i++){
			m_geometryData->GetVertex(i, &position, nullptr);
			meshData->boundingBox.AddPoint(position);
		}
	}
}

rMeshData* rModelData::GetMeshData(const rString& name) const{
	auto result = m_meshes.find(name);

	if (result == m_meshes.end()){
		return nullptr;
	}
	else {
		return result->second.get();
	}
}

void rModelData::GetMeshDataNames(rArrayString& names) const{
	for (auto& entry : m_meshes)
		names.push_back(entry.first);
}

void rModelData::Clear(){
	m_geometryData->Clear();
	m_meshes.clear();
}