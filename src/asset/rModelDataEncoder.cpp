#include "rModelDataEncoder.hpp"

int rModelDataEncoder::Encode(rModelData* modelData, std::ostream* stream){
	m_error = InitEncoder(modelData, stream);

	if (m_error)
		return m_error;
	
	m_error = EncodeHeader();
	
	if (m_error)
		return m_error;
	
	m_error = EncodeTextures();
	
	if (m_error)
		return m_error;
	
	m_error = EncodeMaterials();
	
	if (m_error)
		return m_error;
	
	m_error = EncodeMeshes();
	
	return m_error;
}

int rModelDataEncoder::InitEncoder(rModelData* modelData, std::ostream* stream){
		if (modelData == NULL || stream == NULL)
			return 1;
	
		m_error = 0;
		m_modelData = modelData;
		m_stream = stream;
		
		return m_error;
}

int rModelDataEncoder::EncodeHeader(){
	rModelHeader header;
	header.magicNumber = R_MODEL_MAGIC_NUMBER;
	header.version = R_MODEL_VERSION_NUMBER;
	header.numMeshes = m_modelData->NumMeshes();
	header.numMaterials = m_modelData->NumMaterials();
	header.numTextures = m_modelData->NumTextures();
	
	m_stream->write((char*)&header , sizeof (header));
	
	return 0;
}

int rModelDataEncoder::EncodeTextures(){
	return 0;
}

int rModelDataEncoder::EncodeTexture(rTextureData* texture){
	return 0;
}

int rModelDataEncoder::EncodeMaterials(){
	rMaterialData* material;
	for (size_t i =0; i < m_modelData->NumMaterials(); i++){
		material = m_modelData->GetMaterial(i);
		EncodeMaterial(material);
	}
	
	return 0;
}

int rModelDataEncoder::EncodeMaterial(rMaterialData* material){
	EncodeString(material->m_name);
	size_t texCount = material->m_textures.size();
	m_stream->write((char*)&texCount , sizeof (size_t));
	
	for (size_t i =0; i < texCount; i++)
		EncodeString(material->m_textures[i]);
	
	return 0;
}

void rModelDataEncoder::EncodeString(const rString& str){
	size_t nameSize = str.length();
	m_stream->write((char*)&nameSize , sizeof(size_t));
	m_stream->write(str.c_str() , nameSize);
}

int rModelDataEncoder::EncodeMeshes(){
	for (size_t i =0; i < m_modelData->NumMeshes(); i++)
		EncodeMesh(m_modelData->GetMesh(i));
	
	return 0;
}

int rModelDataEncoder::EncodeMesh(rMeshData* mesh){
	rMeshInfo info;
	mesh->GetInfo(info);
	
	m_stream->write((char*)&info, sizeof(info));
	EncodeString(mesh->m_name);
	
	m_stream->write((char*)&mesh->m_verticies[0] , mesh->NumVertices() * sizeof(rVector3));
	m_stream->write((char*)&mesh->m_normals[0] , mesh->NumVertices() * sizeof(rVector3));
	m_stream->write((char*)&mesh->m_texCoords[0] , mesh->NumVertices() * sizeof(rVector2));
	m_stream->write((char*)&mesh->m_faces[0] , mesh->NumFaces() * sizeof(rMeshFace));
	
	return 0;
}
