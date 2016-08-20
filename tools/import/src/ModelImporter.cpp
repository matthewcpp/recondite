#include "ModelImporter.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace recondite { namespace import {
	void ImportMeshes(const aiScene* scene, ModelData& modelData);

	struct ModelImporter::Impl{
		Assimp::Importer importer;
	};

	ModelImporter::ModelImporter(){
		_impl = new Impl();
	}

	ModelImporter::~ModelImporter(){
		delete _impl;
	}

	int ModelImporter::ImportModel(const rString& path, ModelData& modelData){
		const aiScene* scene = _impl->importer.ReadFile(path.c_str(),
			aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			aiProcess_SortByPType);

		if (!scene)
			return 1;

		ImportMeshes(scene, modelData);

		modelData.CalculateBoundings();

		return 0;
	}

	void ImportMeshes(const aiScene* scene, ModelData& modelData) {
		GeometryData* geometry = modelData.GetGeometryData();
		size_t baseIndex = geometry->VertexCount();

		for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
			MeshData* meshData = modelData.CreateTriangleMesh();
			aiMesh* mesh = scene->mMeshes[i];

			geometry->PushVertices((rVector3*)mesh->mVertices, mesh->mNumVertices);
			geometry->PushNormals((rVector3*)mesh->mNormals, mesh->mNumVertices);

			for (size_t f = 0; f < mesh->mNumFaces; f++) {
				aiFace face = mesh->mFaces[f];
				meshData->Push(face.mIndices[0] + baseIndex, face.mIndices[1] + baseIndex, face.mIndices[2] + baseIndex);
			}
		}
	}

}}