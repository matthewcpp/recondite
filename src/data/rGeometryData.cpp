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

void rElementBufferData::Push(unsigned short v1, unsigned short v2){
	m_elementData.push_back(v1);
	m_elementData.push_back(v2);
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

const int rGeometryData::magicNumber = 1868916594;

rGeometryData::rGeometryData(){
	Clear();
}

rGeometryData::rGeometryData(const rString& path){
	ReadFromFile(path);
}

rGeometryData::rGeometryData(std::istream& stream){
	ReadFromStream(stream);
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

void rGeometryData::SetVertex(size_t index, float x, float y, float z){
	size_t i = VertexElementSize() * index;

	m_vertexData[i] = x;
	m_vertexData[i + 1] = y;
	m_vertexData[i + 2] = z;
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

size_t rGeometryData::VertexFloatCount() const{
	size_t vertexSize = m_vertexElementSize;
	
	if (m_hasTextureCoords)
		vertexSize += 2;
	
	if (m_hasNormals)
		vertexSize += 3;
	
	return vertexSize;
}

size_t rGeometryData::VertexSizeInBytes() const{
	 return VertexFloatCount()* sizeof(float);
}

size_t rGeometryData::VertexCount() const{
	return m_vertexData.size() / VertexFloatCount();
}

size_t rGeometryData::VertexDataSizeInBytes() const{
	return VertexDataCount() * sizeof(float);
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

rContentError rGeometryData::WriteToFile(const rString& path){
	std::ofstream file (path.c_str(), std::ios::binary);

	rContentError error = WriteToStream(file);
	return error;
}

rContentError rGeometryData::WriteToStream(std::ostream& stream){
	if (stream){
		rContentError error = WriteFileHeader(stream);
		stream.write((char*)&m_vertexData[0], VertexDataSizeInBytes());
		error = WriteElementBufferData(stream);

		return error;
	}
	else{
		return rCONTENT_ERROR_STREAM_ERROR;
	}
}

rContentError rGeometryData::WriteFileHeader(std::ostream& stream){
	char texCoords = char(m_hasTextureCoords);
	char normals = char(m_hasNormals);
	size_t vertexCount = VertexCount();
	size_t elementBufferCount = m_elementBuffers.size();
	
	stream.write((char*)&magicNumber, 4);
	stream.write((char*)&m_vertexElementSize, 4);
	stream.write(&texCoords, 1);
	stream.write(&normals, 1);
	stream.write((char*)&vertexCount, 4);
	stream.write((char*)&elementBufferCount, 4);

	return rCONTENT_ERROR_NONE;
}

rContentError rGeometryData::WriteElementBufferData(std::ostream& stream){
	size_t nameLength, elementCount;
	int type;
	
	for (rElementBufferDataMap::const_iterator it = m_elementBuffers.begin(); it != m_elementBuffers.end(); ++it){
		rElementBufferData* bufferData = it->second;
		
		nameLength = it->first.size();
		stream.write((char*)&nameLength, 4);
		stream.write(it->first.data(), nameLength);
		
		type = int(bufferData->GeometryType());
		stream.write((char*)&type, 4);
		
		elementCount = bufferData->ElementCount();
		stream.write((char*)&elementCount, 4);
		stream.write((char*)bufferData->GetElementData(), elementCount * 2);
	}
	return rCONTENT_ERROR_NONE;
}

rContentError rGeometryData::ReadFromFile(const rString& path){
	std::ifstream file(path.c_str(), std::ios::binary);

	m_error = ReadFromStream(file);
	return m_error;
}

rContentError rGeometryData::ReadFromStream(std::istream& stream){
	Clear();

	rContentError error = rCONTENT_ERROR_NONE;

	if (stream){
		size_t vertexCount = 0;
		size_t elementBufferCount = 0;
	
		error = ReadFileHeader(stream, vertexCount, elementBufferCount);
	
		Allocate(m_vertexElementSize, vertexCount, m_hasTextureCoords, m_hasNormals);
		size_t dataSize = VertexDataSizeInBytes();

		stream.read((char*)&m_vertexData[0], dataSize);
		std::streamsize bytesRead = stream.gcount();

		if (bytesRead != dataSize)
			error = rCONTENT_ERROR_STREAM_ERROR;
	
		if (!error)
			error = ReadElementBufferData(stream, elementBufferCount);
	}
	else{
		error = rCONTENT_ERROR_STREAM_ERROR;
	}

	return error;
}

rContentError rGeometryData::ReadFileHeader(std::istream& stream, size_t& vertexCount, size_t& elementBufferCount){
	int magic;
	char boolVal;
	

	stream.read((char*)&magic, 4);
	stream.read((char*)&m_vertexElementSize, 4);
	stream.read((char*)&boolVal, 1);
	m_hasTextureCoords = (boolVal == 1);
	stream.read((char*)&boolVal, 1);
	m_hasNormals = (boolVal == 1);

	stream.read((char*)&vertexCount, 4);
	stream.read((char*)&elementBufferCount, 4);

	return rCONTENT_ERROR_NONE;
}

rContentError rGeometryData::ReadElementBufferData(std::istream& stream, size_t count){
	size_t nameLength, elementCount;
	rGeometryType type;
	rCharArray charBuffer;
	
	for (size_t i = 0; i < count; i++){
		stream.read((char*)&nameLength, 4);
		charBuffer.resize(nameLength);
		stream.read(&charBuffer[0], nameLength);
		rString name(&charBuffer[0], nameLength);
		
		rElementBufferData* bufferData = CreateElementBuffer(name);
		
		stream.read((char*)&type, 4);
		stream.read((char*)&elementCount, 4);
		
		bufferData->SetGeometryType(type);
		bufferData->Allocate(elementCount);
		
		stream.read((char*)bufferData->GetElementData(), elementCount * 2);
	}
	
	return rCONTENT_ERROR_NONE;
}
