#include "data/rGeometryData.hpp"

rElementBufferData::rElementBufferData(rGeometryType geometryType){
	Clear();

	m_geometryType = geometryType;
}

rElementBufferData::rElementBufferData(unsigned short* elements, size_t elementCount, rGeometryType type){
	SetElementData(elements, elementCount, type);
}

void rElementBufferData::SetElementData(unsigned short* elements, size_t elementCount, rGeometryType type){
	m_elementData.resize(elementCount);
	size_t dataSize = elementCount * sizeof(unsigned short);

	memcpy(&m_elementData[0], elements, dataSize);

	m_geometryType = type;
}

size_t rElementBufferData::ElementDataSize() const{
	return ElementCount() * sizeof (unsigned short);
}

size_t rElementBufferData::ElementCount() const{
	return m_elementData.size();
}

void rElementBufferData::Allocate(size_t count){
	m_elementData.resize(count);
}

const unsigned short* rElementBufferData::GetElementData() const{
	if (m_elementData.size())
		return &m_elementData[0];
	else
		return NULL;
}

void rElementBufferData::Clear(){
	m_elementData.clear();
	m_geometryType = rGEOMETRY_TRIANGLES;
}

void rElementBufferData::Push(unsigned short v1, unsigned short v2, unsigned short v3){
	m_elementData.push_back(v1);
	m_elementData.push_back(v2);
	m_elementData.push_back(v3);
}

void rElementBufferData::Push(unsigned short v1, unsigned short v2){
	m_elementData.push_back(v1);
	m_elementData.push_back(v2);
}

rGeometryType rElementBufferData::GeometryType() const{
	return m_geometryType;

}
void rElementBufferData::SetGeometryType(rGeometryType type){
	m_geometryType = type;
}

//-------------------------------------------------------




rElementBufferData* rGeometryData::CreateElementBuffer(const rString& name, rGeometryType geometryType){
	if (m_elementBuffers.count(name)){
		return nullptr;
	}
	else {
		rElementBufferDataPtr bufferDataPtr = std::make_shared<rElementBufferData>(geometryType);
		m_elementBuffers[name] = bufferDataPtr;
		return bufferDataPtr.get();
	}
}

size_t rGeometryData::ElementBufferCount() const{
	return m_elementBuffers.size();
}

void rGeometryData::RemoveElementBuffer(const rString& name){
	m_elementBuffers.erase(name);
}

rElementBufferData* rGeometryData::GetElementBuffer(const rString& name) const{
	auto result = m_elementBuffers.find(name);
	
	if (result == m_elementBuffers.end())
		return nullptr;
	else
		return result->second.get();
}

void rGeometryData::GetElementBufferNames(rArrayString& names) const {
	names.clear();
	
	for (rElementBufferDataMap::const_iterator it = m_elementBuffers.begin(); it != m_elementBuffers.end(); ++it)
		names.push_back(it->first);
}

void rGeometryData::Clear(){
	m_elementBuffers.clear();
	m_vertexBoneLinks.clear();
	m_path.clear();
}

size_t rGeometryData::VertexBoneLinkCount() const{
	return m_vertexBoneLinks.size();
}

size_t rGeometryData::CreateVertexBoneLink(unsigned short vertexIndex, unsigned short boneIndex, float weight){
	rVertexBoneLink boneLink(vertexIndex, boneIndex, weight);
	m_vertexBoneLinks.push_back(boneLink);
	return m_vertexBoneLinks.size();
}

bool rGeometryData::GetVertexBoneLink(size_t index, rVertexBoneLink& boneLink){
	if (index < m_vertexBoneLinks.size()){
		boneLink = m_vertexBoneLinks[index];
		return true;
	}
	else {
		return false;
	}
}