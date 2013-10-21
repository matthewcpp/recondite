#include "data/rGeometryData.hpp"

rElementBufferData::rElementBufferData(){
	Clear();
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

size_t rGeometryData::Allocate(size_t vertexElementSize, size_t vertexCount, bool texCoords, bool normals){
	m_vertexElementSize = vertexElementSize;
	m_hasTextureCoords = texCoords;
	m_hasNormals = normals;
	
	size_t dataSize = VertexSizeInBytes() * vertexCount;
	size_t vertexDataCount = dataSize / 4;

	m_vertexData.resize(vertexDataCount);
	
	return dataSize;
}

void rGeometryData::SetVertex(size_t index, const rVector3& v, const rVector2& tc, const rVector3& n){
	size_t i = VertexElementSize() * index;

	memcpy(&m_vertexData[i], &v, 12);
	memcpy(&m_vertexData[i + 3], &tc, 8);
	memcpy(&m_vertexData[i + 5], &n, 12);
}

void rGeometryData::SetVertex(size_t index, const rVector3& v, const rVector2& tc){
	size_t i = VertexElementSize() * index;

	memcpy(&m_vertexData[i], &v, 12);
	memcpy(&m_vertexData[i + 3], &tc, 8);
}

void rGeometryData::SetVertex(size_t index, float x, float y){
	size_t i = VertexElementSize() * index;

	m_vertexData[i] = x;
	m_vertexData[i + 1] = y;


}

void rGeometryData::SetVertex(size_t index, float x, float y, float u, float v){
	size_t i = 4 * index;
	
	m_vertexData[i] = x;
	m_vertexData[i + 1] = y;
	m_vertexData[i + 2] = u;
	m_vertexData[i + 3] = v;
}

void rGeometryData::SetVertex(size_t index, const rVector2& v){
	SetVertex(index, v.x, v.y);
}

void rGeometryData::SetVertexData(float* vertexData, size_t vertexElementSize, size_t vertexCount, bool texCoords, bool normals){
	size_t dataSize = Allocate(vertexElementSize, vertexCount, texCoords, normals);
	
	memcpy(&m_vertexData[0], vertexData, dataSize);
}

const float* rGeometryData::GetVertexData() const{
	if (m_vertexData.size())
		return &m_vertexData[0];
	else
		return NULL;
}

size_t rGeometryData::VertexElementSize() const{
	return m_vertexElementSize;
}

size_t rGeometryData::VertexSizeInBytes() const{
	size_t vertexSize = m_vertexElementSize;
	
	if (m_hasTextureCoords)
		vertexSize += 2;
	
	if (m_hasNormals)
		vertexSize += 3;
	
	return vertexSize * sizeof(float);
}

size_t rGeometryData::VertexDataSizeInBytes() const{
	return VertexDataCount() * VertexSizeInBytes();
}

size_t rGeometryData::VertexDataCount() const{
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

rElementBufferData* rGeometryData::CreateElementBuffer(const rString& name, unsigned short* elements, size_t elementCount, rGeometryType type){
	rElementBufferData* buffer = CreateElementBuffer(name);
	
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
