#include "ModelImporter.hpp"

#include <map>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "rPath.hpp"

#include "stream/rOFileStream.hpp"

namespace recondite { namespace import {
	

	struct ModelImporter::Impl{
		Assimp::Importer importer;
		ModelImporterOptions options;
		rString path;

		int ImportMaterials(const aiScene* scene, ModelData& modelData);
		void ImportMeshes(const aiScene* scene, ModelData& modelData);
		void ImportVertexWeights(const aiScene* scene, aiMesh* mesh, ModelData& modelData, size_t baseIndex);
		void CreateSkeletonHierarchy(const aiScene* scene, ModelData& modelData);
		void ImportAnimations(const aiScene* scene, ModelData& modelData);
		void NodeDump(const rString& path, const aiScene* scene);
		void NodeWalk(rOStream& stream, size_t indent, aiNode* node);

		void GatherBones(aiNode* node, Skeleton* skeleton);
	};

	ModelImporter::ModelImporter(){
		_impl = new Impl();
	}

	ModelImporter::~ModelImporter(){
		delete _impl;
	}

	void ModelImporter::Impl::NodeDump(const rString& path, const aiScene* scene) {
		rOFileStream stream(path);

		NodeWalk(stream, 0, scene->mRootNode);
	}

	void ModelImporter::Impl::NodeWalk(rOStream& stream, size_t indent, aiNode* node) {
		for (size_t i = 0; i < indent; i++)
			stream << ' ';

		stream << node->mName.C_Str() << '\n';

		for (size_t i = 0; i < node->mNumChildren; i++) {
			NodeWalk(stream, indent + 2, node->mChildren[i]);
		}
	}

	int ModelImporter::ImportModel(const rString& path, ModelData& modelData, const ModelImporterOptions& options){
		_impl->path = path;
		_impl->options = options;

		const aiScene* scene = _impl->importer.ReadFile(path.c_str(),
			aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			aiProcess_SortByPType |
			aiProcess_GenSmoothNormals);

		if (!scene)
			return 1;

		_impl->NodeDump("C:/temp/node_dump.txt", scene);

		if (_impl->options.importSkeleton) {
			modelData.CreateSkeleton();
			_impl->CreateSkeletonHierarchy(scene, modelData);
		}

		if (scene->mNumAnimations > 0 && _impl->options.importAnimations) {
			_impl->ImportAnimations(scene, modelData);
		}

		if (_impl->options.importMeshData) {
			_impl->ImportMaterials(scene, modelData);
			_impl->ImportMeshes(scene, modelData);
			modelData.CalculateBoundings();
		}

		return 0;
	}

	void ModelImporter::Impl::ImportMeshes(const aiScene* scene, ModelData& modelData) {
		GeometryData* geometry = modelData.GetGeometryData();
		size_t baseIndex = geometry->VertexCount();

		for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
			MeshData* meshData = modelData.CreateTriangleMesh();
			aiMesh* mesh = scene->mMeshes[i];

			if (mesh->mName.length > 0) {
				meshData->SetName(mesh->mName.C_Str());
			}

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

			if (scene->mNumAnimations > 0 && options.importSkeleton)
				ImportVertexWeights(scene, mesh, modelData, baseIndex);

			baseIndex += mesh->mNumVertices;
		}
	}

	void ModelImporter::Impl::ImportVertexWeights(const aiScene* scene, aiMesh* mesh, ModelData& modelData, size_t baseIndex) {
		GeometryData* geometryData = modelData.GetGeometryData();
		geometryData->AllocateVertexWeightData(mesh->mNumVertices);

		Skeleton* skeleton = modelData.GetSkeleton();


		for (size_t i = 0; i < mesh->mNumBones; i++) {
			aiBone* bone = mesh->mBones[i];

			Bone* boneData = skeleton->GetBoneByName(bone->mName.C_Str());

			for (uint32_t j = 0; j < bone->mNumWeights; j++) {
				geometryData->AddVertexWeight(baseIndex + bone->mWeights[j].mVertexId, boneData->id, bone->mWeights[j].mWeight);
			}
				
		}
	}

	void ModelImporter::Impl::GatherBones(aiNode* node, Skeleton* skeleton) {
		Bone* bone = skeleton->CreateBone(node->mName.C_Str());

		rMatrix4 transformMatrix((float*)&node->mTransformation);
		transformMatrix.Transpose();
		bone->transform = transformMatrix;

		Bone* parentBone = skeleton->GetBoneByName(node->mParent->mName.C_Str());

		if (parentBone) {
			bone->parentId = parentBone->id;
			parentBone->children.push_back(bone->id);
		}

		for (size_t i = 0; i < node->mNumChildren; i++) {
			GatherBones(node->mChildren[i], skeleton);
		}
	}

	void ModelImporter::Impl::CreateSkeletonHierarchy(const aiScene* scene, ModelData& modelData) {
		//Need to find child of root node which does not refer to meshes.  This will be the Skeleton Container.
		aiNode* rootNode = scene->mRootNode;
		aiNode* skeletonContainer = nullptr;
		Skeleton* skeleton = modelData.GetSkeleton();

		for (size_t i = 0; i < rootNode->mNumChildren; i++) {
			if (rootNode->mChildren[i]->mNumMeshes == 0) {
				skeletonContainer = rootNode->mChildren[i];
				break;
			}
		}

		//extract bone hierarchy from assimp node tree
		for (size_t i = 0; i < skeletonContainer->mNumChildren; i++) {
			GatherBones(skeletonContainer->mChildren[i], skeleton);
		}

		skeleton->CacheBoneData();
	}

	void ModelImporter::Impl::ImportAnimations(const aiScene* scene, ModelData& modelData) {
		Skeleton* skeleton = modelData.GetSkeleton();

		for (size_t i = 0; i < scene->mNumAnimations; i++) {
			aiAnimation* sourceAnimation = scene->mAnimations[i];
			Animation* animation = skeleton->CreateAnimation(sourceAnimation->mName.C_Str(), sourceAnimation->mDuration);

			if (!animation) continue;

			for (size_t i = 0; i < sourceAnimation->mNumChannels; i++) {
				aiNodeAnim* nodeAnim = sourceAnimation->mChannels[i];
				Bone* bone = skeleton->GetBoneByName(nodeAnim->mNodeName.C_Str());

				if (bone) {
					AnimationChannel* boneAnimation = animation->CreateChannelForBone(bone->id);

					for (size_t i = 0; i < nodeAnim->mNumPositionKeys; i++) {
						aiVectorKey* k = nodeAnim->mPositionKeys + i;
						boneAnimation->translationKeys.times.push_back(k->mTime);
						boneAnimation->translationKeys.values.emplace_back(k->mValue.x, k->mValue.y, k->mValue.z);
					}

					for (size_t i = 0; i < nodeAnim->mNumScalingKeys; i++) {
						aiVectorKey* k = nodeAnim->mScalingKeys + i;
						boneAnimation->scaleKeys.times.push_back(k->mTime);
						boneAnimation->scaleKeys.values.emplace_back(k->mValue.x, k->mValue.y, k->mValue.z);
					}

					for (size_t i = 0; i < nodeAnim->mNumRotationKeys; i++) {
						aiQuatKey* k = nodeAnim->mRotationKeys + i;
						boneAnimation->rotationKeys.times.push_back(k->mTime);
						boneAnimation->rotationKeys.values.emplace_back(k->mValue.x, k->mValue.y, k->mValue.z, k->mValue.w);
					}
				}
			}
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