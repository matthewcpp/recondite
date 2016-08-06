#include "ModelImporter.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace recondite { namespace import {

	struct ModelImporter::Impl{
		Assimp::Importer importer;
	};

	ModelImporter::ModelImporter(){
		_impl = new Impl();
	}

	ModelImporter::~ModelImporter(){
		delete _impl;
	}

	int ModelImporter::ImportModel(const rString& path, rModelData& modelData){
		const aiScene* scene = _impl->importer.ReadFile(path.c_str(),
			aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			aiProcess_SortByPType);

		if (!scene)
			return 1;

		return 0;
	}

}}