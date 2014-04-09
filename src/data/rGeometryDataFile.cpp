#include "data/rGeometryDataFile.hpp"

#include <iostream>

rGeometryDataReader::rGeometryDataReader(){
	m_geometryData = NULL;
	m_error = rCONTENT_ERROR_NONE;
}

rContentError rGeometryDataReader::GetError() const{
	return m_error;
}

rContentError rGeometryDataReader::ReadFromFile(const rString& path, rGeometryData& geometryData){
	std::ifstream file(path.c_str(), std::ios::binary);

	if (file){
		ReadFromStream(file, geometryData);
	}
	else{
		m_error = rCONTENT_ERROR_FILE_NOT_FOUND;
	}

	geometryData.SetPath(path);

	return m_error;
}

rContentError rGeometryDataReader::ReadFromStream(std::istream& stream, rGeometryData& geometryData){
	m_geometryData = &geometryData;
	m_error = rCONTENT_ERROR_NONE;
	m_geometryData->Clear();

	ReadHeader(stream);

	if (!m_error){
		ReadVertexData(stream);
	}

	if (!m_error)
		ReadElementBufferData(stream);

	if (!m_error)
		ReadVertexBoneLinks(stream);

	return m_error;
}

void rGeometryDataReader::ReadHeader(std::istream& stream){
	stream.read((char*)&m_header, sizeof (rGeometryFileHeader));

	if (m_header.magicNumber != rGEOMETRY_MAGIC_NUMBER || m_header.version != 1){
		m_error = rCONTENT_ERROR_FILE_NOT_READABLE;
	}

	if (!stream)
		m_error = rCONTENT_ERROR_PARSE_ERROR;
}

void rGeometryDataReader::ReadVertexData(std::istream& stream){
	m_geometryData->Allocate(m_header.vertexCount);
	char* dataPtr = m_geometryData->VertexData();
	stream.read(dataPtr, m_header.vertexCount * sizeof(rModelVertex));

	if (!stream)
		m_error = rCONTENT_ERROR_PARSE_ERROR;
}

void rGeometryDataReader::ReadElementBufferData(std::istream& stream){
	size_t nameLength, elementCount;
	rGeometryType type;
	rCharArray charBuffer;
	
	for (size_t i = 0; i < m_header.elementBufferCount; i++){
		stream.read((char*)&nameLength, 4);
		charBuffer.resize(nameLength);
		stream.read(&charBuffer[0], nameLength);
		rString name(&charBuffer[0], nameLength);
		
		rElementBufferData* bufferData = m_geometryData->CreateElementBuffer(name);
		
		stream.read((char*)&type, 4);
		stream.read((char*)&elementCount, 4);
		
		bufferData->SetGeometryType(type);
		bufferData->Allocate(elementCount);
		
		stream.read((char*)bufferData->GetElementData(), elementCount * 2);
	}
	
	if (!stream)
		m_error = rCONTENT_ERROR_PARSE_ERROR;
}

void rGeometryDataReader::ReadVertexBoneLinks(std::istream& stream){
	rVertexBoneLink link;

	for (size_t i = 0; i < m_header.vertexBoneLinkCount; i++){
		stream.read((char*)&link, sizeof(rVertexBoneLink));

		m_geometryData->CreateVertexBoneLink(link.vertexIndex, link.boneIndex, link.weight);
	}

	if (!stream)
		m_error = rCONTENT_ERROR_PARSE_ERROR;
}


//----------------------------------------------------------------

rGeometryDataWriter::rGeometryDataWriter(){
	m_geometryData = NULL;
	m_error = rCONTENT_ERROR_NONE;
}

rContentError rGeometryDataWriter::GetError() const{
	return m_error;
}

rContentError rGeometryDataWriter::WriteToFile(const rString& path, const rGeometryData& geometryData){
	std::ofstream file (path.c_str(), std::ios::binary);

	if (file){
		WriteToStream(file, geometryData);
	}
	else{
		m_error = rCONTENT_ERROR_FILE_NOT_WRITABLE;
	}

	return m_error;
}

rContentError rGeometryDataWriter::WriteToStream(std::ostream& stream, const rGeometryData& geometryData){
	m_geometryData = &geometryData;
	m_error = rCONTENT_ERROR_NONE;

	WriteFileHeader(stream);

	if (!m_error)
		WriteVertexData(stream);

	if (!m_error)
		WriteElementBufferData(stream);

	if (!m_error)
		WriteVertexBoneLinks(stream);

	return m_error;
}

void rGeometryDataWriter::WriteFileHeader(std::ostream& stream){
	m_header.magicNumber = rGEOMETRY_MAGIC_NUMBER;
	m_header.version = 1;
	m_header.vertexCount = m_geometryData->VertexCount();
	m_header.elementBufferCount = m_geometryData->ElementBufferCount();
	m_header.vertexBoneLinkCount = m_geometryData->VertexBoneLinkCount();

	stream.write((char*)&m_header, sizeof(rGeometryFileHeader));

	if (!stream)
		m_error = rCONTENT_ERROR_STREAM_ERROR;
}

void rGeometryDataWriter::WriteVertexData(std::ostream& stream){
	stream.write(m_geometryData->VertexData(), m_header.vertexCount * sizeof (rModelVertex));

	if (!stream)
		m_error = rCONTENT_ERROR_STREAM_ERROR;
}

void rGeometryDataWriter::WriteElementBufferData(std::ostream& stream){
	rArrayString bufferNames;
	m_geometryData->GetElementBufferNames(bufferNames);

	size_t nameLength, elementCount;
	int type;

	for (size_t i =0; i < bufferNames.size(); i++){
		rElementBufferData* bufferData = m_geometryData->GetElementBuffer(bufferNames[i]);

		nameLength = bufferNames[i].size();
		stream.write((char*)&nameLength, 4);
		stream.write(bufferNames[i].c_str(), nameLength);
		
		type = int(bufferData->GeometryType());
		stream.write((char*)&type, 4);
		
		elementCount = bufferData->ElementCount();
		stream.write((char*)&elementCount, 4);
		stream.write((char*)bufferData->GetElementData(), elementCount * 2);
	}
	
	if (!stream)
		m_error = rCONTENT_ERROR_STREAM_ERROR;
}

void rGeometryDataWriter::WriteVertexBoneLinks(std::ostream& stream){
	const rVertexBoneLinkMap& vertexBoneLinks = m_geometryData->VertexBoneLinks();
	rVertexBoneLinkMap::const_iterator end = vertexBoneLinks.end();

	for (rVertexBoneLinkMap::const_iterator it = vertexBoneLinks.begin(); it != end; ++it){
		rVertexBoneLink link = it->second;
		stream.write((char*)&link, sizeof (rVertexBoneLink));
	}
}