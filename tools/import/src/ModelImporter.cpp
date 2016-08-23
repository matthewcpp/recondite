#include "ModelImporter.hpp"

#include <map>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "rPath.hpp"

namespace recondite { namespace import {
	void ImportMeshes(const aiScene* scene, ModelData& modelData);

	struct ModelImporter::Impl{
		Assimp::Importer importer;
		rString path;

		int ImportMaterials(const aiScene* scene, ModelData& modelData);
	};

	ModelImporter::ModelImporter(){
		_impl = new Impl();
	}

	ModelImporter::~ModelImporter(){
		delete _impl;
	}

	int ModelImporter::ImportModel(const rString& path, ModelData& modelData){
		_impl->path = path;
		const aiScene* scene = _impl->importer.ReadFile(path.c_str(),
			aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			aiProcess_SortByPType |
			aiProcess_GenSmoothNormals);

		if (!scene)
			return 1;

		_impl->ImportMaterials(scene, modelData);
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

			if (mesh->mNumUVComponents[0] > 0) {
				aiVector3D* texCoords = mesh->mTextureCoords[0];
				rVector2 texCoord;

				for (unsigned int tc = 0; tc < mesh->mNumVertices; tc++) {
					texCoord.Set(texCoords[tc].x, texCoords[tc].y);
					geometry->PushTexCoord(texCoord);
				}
			}

			for (size_t f = 0; f < mesh->mNumFaces; f++) {
				aiFace face = mesh->mFaces[f];
				meshData->Push(face.mIndices[0] + baseIndex, face.mIndices[1] + baseIndex, face.mIndices[2] + baseIndex);
			}

			meshData->SetMaterialId(mesh->mMaterialIndex);

			baseIndex += mesh->mNumVertices;
		}
	}

	int ModelImporter::Impl::ImportMaterials(const aiScene* scene, ModelData& modelData) {
		std::map<rString, size_t> textureMap;

		for (unsigned int m = 0; m<scene->mNumMaterials; ++m)
		{
			MaterialData* materialData = modelData.CreateMaterial();

			int texIndex = 0; // for now just get first texture index, however there can be multiple
			aiString texturePath;  

			aiReturn texFound = scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, texIndex, &texturePath);
			if (texFound == AI_SUCCESS) {
				rString directory = rPath::Directory(path);
				rString texPath = texturePath.C_Str();

				if (textureMap.count(texPath) == 0) { //texture file not already loaded
					size_t textureId = modelData.GetNumTextures();
					rTextureData* textureData = modelData.CreateTexture();
					ImageImporter imageImporter;
					int result = 0;

					if (texPath[0] == '*') { //signals embedded texture
						aiTexture* texture = scene->mTextures[0];
						result = imageImporter.ImportImage((const char *)texture->pcData, texture->mWidth, *textureData);
					}
					else { //load the texture from File
						rString textureFilePath = rPath::Combine(directory, texPath);
						result = imageImporter.ImportImage(textureFilePath, *textureData);
					}


					if (result != 0) continue;
					else {
						textureMap[texPath] = textureId;
						materialData->diffuseTextureId = textureId;
					}
				}
				else { //file already loaded in this model
					materialData->diffuseTextureId = textureMap[texPath];
				}
			}
		}

		return 0;
	}

}}