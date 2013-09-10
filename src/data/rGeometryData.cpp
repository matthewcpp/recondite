#include "data/rGeometryData.hpp"


rElementBufferData::rElementBufferData(){}

rElementBufferData::rElementBufferData(unsigned short* elements, size_t elementCount){
	SetElementData(elements, elementCount);
}

void rElementBufferData::SetElementData(unsigned short* elements, size_t elementCount){
	m_elementData.resize(elementCount);
	size_t dataSize = elementCount * sizeof(unsigned short);
	
	memcpy(&m_elementData[0], elements, dataSize);
}

size_t rElementBufferData::ElementDataSize() const{
	return ElementCount() * sizeof (unsigned short);
}

size_t rElementBufferData::ElementCount() const{
	return m_elementData.size();
}

const unsigned short* rElementBufferData::GetElementData() const{
	if (m_elementData.size())
		return &m_elementData[0];
	else
		return NULL;
}

void rElementBufferData::Clear(){
	m_elementData.clear();
}

//-------------------------------------------------------

rGeometryData::rGeometryData(){
	Clear();
}

rGeometryData::~rGeometryData(){
	Clear();
}

size_t rGeometryData::Allocate(size_t vertexSize, size_t vertexCount, bool texCoords, bool normals){
	m_vertexSize = vertexSize;
	m_hasTextureCoords = texCoords;
	m_hasNormals = normals;
	
	size_t dataSize = VertexSizeInBytes() * vertexCount;
	
	m_vertexData.resize(dataSize);
	
	return dataSize;
}

void rGeometryData::SetVertex(size_t index, float x, float y){
	size_t i = VertexSizeInBytes() * index;
	
	m_vertexData[i] = x;
	m_vertexData[i + 1] = y;
}

void rGeometryData::SetVertex(size_t index, float x, float y, float u, float v){
	size_t i = VertexSizeInBytes() * index;
	
	m_vertexData[i] = x;
	m_vertexData[i + 1] = y;
	m_vertexData[i + 2] = u;
	m_vertexData[i + 3] = v;
}

void rGeometryData::SetVertexData(float* vertexData, size_t vertexSize, size_t vertexCount, bool texCoords, bool normals){
	size_t dataSize = Allocate(vertexSize, vertexCount, texCoords, normals);
	
	memcpy(&m_vertexData[0], vertexData, dataSize);
}

const float* rGeometryData::GetVertexData() const{
	if (m_vertexData.size())
		return &m_vertexData[0];
	else
		return NULL;
}

size_t rGeometryData::VertexSize() const{
	return m_vertexSize;
}

size_t rGeometryData::VertexSizeInBytes() const{
	size_t vertexSize = m_vertexSize;
	
	if (m_hasTextureCoords)
		vertexSize += 2;
	
	if (m_hasNormals)
		vertexSize += 3;
	
	return vertexSize * sizeof(float);
}

size_t rGeometryData::VertexDataSize() const{
	return VertexCount() * VertexSizeInBytes();
}


size_t rGeometryData::VertexCount() const{
	return m_vertexData.size();
}

bool rGeometryData::HasTextureCoords() const{
	return m_hasTextureCoords;
}

bool rGeometryData::HasNormals() const{
	return m_hasNormals;
}

rElementBufferData* rGeometryData::CreateElementBuffer(const rString& name){
	rElementBufferData* buffer = NULL;
	
	rElementBufferDataMap::iterator result = m_elementBuffers.find(name);
	
	if (result == m_elementBuffers.end()){
		buffer = new rElementBufferData();
		m_elementBuffers[name] = buffer;
	}
	
	return buffer;
}

rElementBufferData* rGeometryData::CreateElementBuffer(const rString& name, unsigned short* elements, size_t elementCount){
	rElementBufferData* buffer = CreateElementBuffer(name);
	
	if (buffer){
		buffer->SetElementData(elements, elementCount);
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
	
	for (rElementBufferDataMap::iterator it = m_elementBuffers.begin(); it != m_elementBuffers.end(); ++it)
		delete it->second;
	
	m_elementBuffers.clear();

	m_hasTextureCoords = false;
	m_hasNormals = false;
	m_error = rCONTENT_ERROR_NONE;
}

rString rGeometryData::Path() const{
	return m_path;
}

rContentError rGeometryData::GetError() const{
	return m_error;
}
