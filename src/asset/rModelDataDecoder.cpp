#include "rModelDataDecoder.hpp"

int rModelDataDecoder::Decode(std::istream* stream, rModelData* modelData){
	
	m_error = InitDecoder(stream , modelData);
	
	if (m_error)
		return m_error;
	
	m_error = DecodeHeader();
	
	if (m_error)
		return m_error;
	
	m_error = DecodeMaterials();
	
	if (m_error)
		return m_error;
	
	m_error = DecodeMeshes();
	
	return m_error;
}


int rModelDataDecoder::InitDecoder(std::istream* stream, rModelData* modelData){
	if (modelData == NULL || stream == NULL)
		return 1;
	
	m_error = 0;
	
	m_modelData = modelData;
	m_stream = stream;
	
	m_modelData->Clear();
	
	return m_error;
}


int rModelDataDecoder::DecodeHeader(){
	m_stream->read((char*)&m_header , sizeof (m_header));
	
	if (m_header.magicNumber != R_MODEL_MAGIC_NUMBER)
		return 1;
	
	return 0;
}

void rModelDataDecoder::DecodeString(rString& str){
	size_t nameSize;
	m_stream->read((char*)&nameSize , sizeof(size_t));
	
	char* buffer = new char[nameSize];
	
	m_stream->read(buffer, nameSize);
	str = rString (buffer, nameSize);
	
	delete [] buffer;
}

int rModelDataDecoder::DecodeMaterial(){
	rString matName, texName;
	size_t texCount;
	
	DecodeString(matName);
	m_stream->read((char*)&texCount, sizeof(texCount));
	rMaterialData* material = m_modelData->CreateMaterial(matName);
	
	for (size_t i = 0; i < texCount; i++){
		DecodeString(texName);
		material->m_textures.push_back(texName);
	}
	
	material->m_source = rASSET_SOURCE_FILE;
	
	return 0;
}

int rModelDataDecoder::DecodeMaterials(){
	for (size_t i = 0; i < m_header.numMaterials; i++)
		DecodeMaterial();
	
	return 0;
}

int rModelDataDecoder::DecodeMeshes(){
	for (size_t i =0; i < m_header.numMeshes; i++)
		DecodeMesh();
	
	return 0;
}

int rModelDataDecoder::DecodeMesh(){
	rMeshInfo info;
	rString meshName;
	
	m_stream->read((char*)&info, sizeof(info));
	DecodeString(meshName);
	
	rMeshData* mesh = m_modelData->CreateMesh(meshName);
	mesh->ResizeArrays(info.numVertices , info.numFaces);

	m_stream->read((char*)&mesh->m_verticies[0] , mesh->NumVertices() * sizeof(rVector3));
	m_stream->read((char*)&mesh->m_normals[0] , mesh->NumVertices() * sizeof(rVector3));
	m_stream->read((char*)&mesh->m_texCoords[0] , mesh->NumVertices() * sizeof(rVector2));
	m_stream->read((char*)&mesh->m_faces[0] , mesh->NumFaces() * sizeof(rMeshFace));
	
	return 0;
}
