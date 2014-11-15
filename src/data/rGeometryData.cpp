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

rGeometryData::rGeometryData(){
	Clear();
}

rGeometryData::~rGeometryData(){
	Clear();
}

void rGeometryData::Allocate(size_t size){
	m_vertexData.resize(size);
}

void rGeometryData::SetVertex(size_t index, const rVector3& v, const rVector3& n, const rVector2& tc){
	if (index < m_vertexData.size()){
		rModelVertex& vertex = m_vertexData[index];

		vertex.position = v;
		vertex.normal = n;
		vertex.texCoord = tc;
	}
	
}

void rGeometryData::PushVertex(const rVector3& v, const rVector3& n, const rVector2& tc){
	rModelVertex vertex(v, n, tc);
	m_vertexData.push_back(vertex);
}

bool rGeometryData::GetVertex(size_t index, rModelVertex& data) const{
	if (index < m_vertexData.size()){
		data = m_vertexData[index];
		return true;
	}
	else{
		return false;
	}
}

void rGeometryData::GetVertex(size_t index, rVector3* position, rVector2* texCoord, rVector3* normal) const {
	if (index >= m_vertexData.size())
		return;

	const rModelVertex& vertex = m_vertexData[index];

	if (position)
		*position = vertex.position;

	if (texCoord)
		*texCoord = vertex.texCoord;

	if (normal)
		*normal = vertex.normal;
}

void rGeometryData::TransformVertex(size_t index, const rMatrix4& transform){
	if (index <  m_vertexData.size()){
		rModelVertex& vertex = m_vertexData[index];

		transform.TransformVector3(vertex.position);
		transform.TransformVector3(vertex.normal);
		vertex.normal.Normalize();
	}
}

const char* rGeometryData::VertexData() const{
	if (m_vertexData.size())
		return (char*)&m_vertexData[0];
	else
		return NULL;
}

char* rGeometryData::VertexData(){
	if (m_vertexData.size())
		return (char*)&m_vertexData[0];
	else
		return NULL;
}

size_t rGeometryData::VertexCount() const{
	return m_vertexData.size();
}

size_t rGeometryData::VertexDataSize() const{
	return m_vertexData.size() * sizeof (rModelVertexArray::value_type);
}


const rVertexBoneLinkMap& rGeometryData::VertexBoneLinks() const{
	return m_vertexBoneLinks;
}

size_t rGeometryData::VertexBoneLinkCount() const{
	return m_vertexBoneLinks.size();
}

void rGeometryData::CreateVertexBoneLink(unsigned short vertexIndex, unsigned short boneIndex, float weight){
	rVertexBoneLink link(vertexIndex, boneIndex, weight);

	m_vertexBoneLinks.insert(std::make_pair(vertexIndex, link));
}

void rGeometryData::CreateVetexBoneDataArray(rVertexBoneDataArray& vertexBoneData) const{
	if (m_vertexBoneLinks.size() > 0){
		size_t vertexCount = VertexCount();
		vertexBoneData.resize(vertexCount);

		int linkNum;
		for (size_t i = 0; i < vertexCount; i++){
			linkNum = 0;
			rVertexBoneLinkResult links = m_vertexBoneLinks.equal_range(i);

			for (rVertexBoneLinkMap::const_iterator it = links.first; it != links.second; ++it){
				vertexBoneData[i].boneIndex[linkNum] = it->second.boneIndex;
				vertexBoneData[i].weight[linkNum] = it->second.weight;
				linkNum++;
			}

			if (linkNum < rMAX_VERTEX_BONE_INFLUENCES){
				vertexBoneData[i].boneIndex[linkNum] = -1;
			}
		}
	}
	else {
		vertexBoneData.clear();
	}
}

rElementBufferData* rGeometryData::CreateElementBuffer(const rString& name, rGeometryType geometryType){
	rElementBufferData* buffer = NULL;
	
	rElementBufferDataMap::iterator result = m_elementBuffers.find(name);
	
	if (result == m_elementBuffers.end()){
		buffer = new rElementBufferData(geometryType);
		m_elementBuffers[name] = buffer;
	}
	
	return buffer;
}

rElementBufferData* rGeometryData::CreateElementBuffer(const rString& name, unsigned short* elements, size_t elementCount, rGeometryType type){
	rElementBufferData* buffer = CreateElementBuffer(name, type);
	
	if (buffer){
		buffer->SetElementData(elements, elementCount, type);
	}
	
	return buffer;
}

size_t rGeometryData::ElementBufferCount() const{
	return m_elementBuffers.size();
}

bool rGeometryData::RemoveElementBuffer(const rString& name){
	rElementBufferDataMap::iterator result = m_elementBuffers.find(name);
	
	if (result == m_elementBuffers.end()){
		return false;
	}
	else{
		delete result->second;
		m_elementBuffers.erase(result);
		return true;
	}
}

rElementBufferData* rGeometryData::GetElementBuffer(const rString& name) const{
	rElementBufferData*  buffer = NULL;
	
	rElementBufferDataMap::const_iterator result = m_elementBuffers.find(name);
	
	if (result != m_elementBuffers.end())
		buffer = result->second;
	
	return buffer;
}

void rGeometryData::GetElementBufferNames(rArrayString& names) const {
	names.clear();
	
	for (rElementBufferDataMap::const_iterator it = m_elementBuffers.begin(); it != m_elementBuffers.end(); ++it)
		names.push_back(it->first);
}

void rGeometryData::Clear(){
	m_vertexData.clear();
	m_path.clear();
	
	rElementBufferDataMap::iterator end = m_elementBuffers.end();
	for (rElementBufferDataMap::iterator it = m_elementBuffers.begin(); it != end; ++it)
		delete it->second;
	
	m_elementBuffers.clear();

	m_vertexBoneLinks.clear();
}

rString rGeometryData::Path() const{
	return m_path;
}

void rGeometryData::SetPath(const rString& path){
	m_path = path;
}