#ifndef RWX_ASSIMP_IMPORTER_HPP
#define RWX_ASSIMP_IMPORTER_HPP

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <sstream>

#include "rModelData.hpp"

class rwxAssimpModelImporter{
public:
	
	bool Import(const char* path, rModelData* modelData);
	
	std::string GetError();
	
private:
	void ImportMaterials(const aiScene* scene);
	void ImportMaterial(aiMaterial* material);
	void ImportMaterialTextures(aiMaterial* material, rMaterialData* matData);
	
	
	void ImportMeshes(const aiScene* scene);
	void ImportMesh(aiMesh* mesh);
	void ImportMeshGeometry(aiMesh* mesh, rGeometryData* geometry);
	
	bool ValidateModel(const aiScene* scene);
	bool ValidateMesh(aiMesh* mesh);
	
private:
	rModelData* m_modelData;
	
	rString m_error;
	rString m_path;
};

#endif
