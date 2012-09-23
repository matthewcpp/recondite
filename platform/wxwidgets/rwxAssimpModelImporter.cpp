#include "rwxAssimpModelImporter.hpp"

bool rwxAssimpModelImporter::Import(const char* path, rModelData* modelData){
	m_modelData = modelData;
	m_modelData->Clear();
	bool imported = false;
	
	Assimp::Importer importer;
	
  const aiScene* scene = importer.ReadFile( path, 
        aiProcess_CalcTangentSpace       | 
        aiProcess_Triangulate            |
        aiProcess_JoinIdenticalVertices  |
        aiProcess_SortByPType);
  
  if (scene){
  	imported = true;
  	m_path = path;
		ImportMaterials(scene);
		ImportMeshes(scene);
	}
	
	if (!ValidateModel(scene))
		return false;
		
	m_error = importer.GetErrorString();
	return imported;
}

void rwxAssimpModelImporter::ImportMaterials(const aiScene* scene){
	std::cout << "Found "<< scene->mNumMaterials << " Materials"<<std::endl;
	
	for (unsigned int i = 0; i < scene->mNumMaterials; i++){
		ImportMaterial(scene->mMaterials[i]);
	}
}

void rwxAssimpModelImporter::ImportMaterial(aiMaterial* material){
	std::stringstream name;
	name << "Material " << m_modelData->NumMaterials();
	
	rMaterialData* matData = m_modelData->CreateMaterial(name.str());
	ImportMaterialTextures(material , matData);
}

void rwxAssimpModelImporter::ImportMaterialTextures(aiMaterial* material, rMaterialData* matData){
	unsigned int textureCount = material->GetTextureCount(aiTextureType_DIFFUSE);
	aiString texPath;
	
	for (unsigned int t = 0; t < textureCount; t++){
		material->GetTexture(aiTextureType_DIFFUSE, t, &texPath);
		
		rTextureData* tex = m_modelData->CreateTexture(rString(texPath.C_Str()));
		tex->m_source = rASSET_SOURCE_FILE;
		matData->AddTexture(tex, rMATERIAL_TEXTURE_DIFFUSE);
	}
}

void rwxAssimpModelImporter::ImportMeshes(const aiScene* scene){
	std::cout << "Found "<< scene->mNumMeshes << " Meshes"<<std::endl;
	
	for (unsigned int i = 0; i < scene->mNumMeshes; i++){
		ImportMesh(scene->mMeshes[i]);
	}
}

void rwxAssimpModelImporter::ImportMesh(aiMesh* mesh){
	std::stringstream meshName;
	
	if (mesh->mName.length > 0)
		meshName << mesh->mName.C_Str();
	else
		meshName << "Mesh " << m_modelData->NumMeshes();

	rString geometryName = meshName.str() + "_geo";
	rGeometryData* geometry = m_modelData->CreateGeometry(geometryName);
	ImportMeshGeometry(mesh, geometry);
	
	m_modelData->CreateMesh(meshName.str(), geometry , m_modelData->GetMaterial(mesh->mMaterialIndex));
}

void rwxAssimpModelImporter::ImportMeshGeometry(aiMesh* mesh, rGeometryData* geometry){
	aiVector3D* vertices = mesh->mVertices;
	aiVector3D* normals = mesh->mNormals;
	aiVector3D* texCoords = mesh->mTextureCoords[0];
	
	geometry->ResizeArrays(mesh->mNumVertices, mesh->mNumFaces);
	
	memcpy(&geometry->m_verticies[0], &vertices[0], mesh->mNumVertices * sizeof(rVector3));
	memcpy(&geometry->m_normals[0], &normals[0], mesh->mNumVertices * sizeof(rVector3));
	
	for (size_t i = 0; i <mesh->mNumFaces; i++){
		memcpy (&geometry->m_faces[i] , mesh->mFaces[i].mIndices, sizeof(rMeshFace));
	}
	
	for (size_t i = 0; i < mesh->mNumVertices; i++){
		geometry->m_texCoords[i].x = texCoords[i].x;
		geometry->m_texCoords[i].y = texCoords[i].y;
	}
}

bool rwxAssimpModelImporter::ValidateModel(const aiScene* scene){
	bool isValid = true;
	for (unsigned int i = 0; i < scene->mNumMeshes; i++){
		isValid = ValidateMesh(scene->mMeshes[i]);
		
		if (!isValid)
			return false;
	}
	
	return isValid;
}

bool rwxAssimpModelImporter::ValidateMesh(aiMesh* mesh){
	return mesh->HasTextureCoords(0) && mesh->HasNormals();
}
