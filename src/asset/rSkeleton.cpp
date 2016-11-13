#include "rSkeleton.hpp"

#include <map>
#include <memory>

namespace recondite {
#define MaxBoneWightsPerVertex 4
#define RootBoneId UINT32_MAX

	bool Bone::IsRoot() const {
		return parentId == RootBoneId;
	}

	struct VertexBoneWeights {
		uint32_t boneIndex[MaxBoneWightsPerVertex];
		float weight[MaxBoneWightsPerVertex];

		VertexBoneWeights();
	};

	VertexBoneWeights::VertexBoneWeights() {
		for (size_t i = 0; i < 4; i++) {
			boneIndex[i] = 0;
			weight[i] = 0.0f;
		}
	}

	struct SkeletonFileHeader {
		uint32_t numBones;
		uint32_t numVertexBoneWeights;
		uint32_t numAnimations;
	};

	struct Skeleton::Impl {
		std::vector <std::unique_ptr<Bone>> bones;
		std::map<rString, Bone*> bonesByName;

		std::vector <std::unique_ptr<Animation>> animations;
		std::map<rString, Animation*> animationsByName;

		std::vector<VertexBoneWeights> vertexBoneWeights;
		rMatrix4 globalTransform;

		void InitHeader(SkeletonFileHeader& header);
	};

	Skeleton::Skeleton() {
		_impl = new Impl();
	}

	Skeleton::~Skeleton() {
		delete _impl;
	}

	Bone* Skeleton::CreateBone(const rString& name) {
		if (_impl->bonesByName.count(name)) {
			return nullptr;
		}
		else {
			Bone* boneData = new Bone();

			_impl->bones.emplace_back(boneData);
			_impl->bonesByName[name] = boneData;

			boneData->name = name;
			boneData->id = _impl->bonesByName.size() - 1;
			boneData->parentId = UINT32_MAX;

			return boneData;
		}
	}


	void Skeleton::AllocateVertexWeightData(size_t numVertices) {
		_impl->vertexBoneWeights.resize(_impl->vertexBoneWeights.size() + numVertices);
	}

	bool Skeleton::AddVertexWeight(size_t vertexIndex, size_t boneIndex, float weight) {
		VertexBoneWeights& boneWeights = _impl->vertexBoneWeights[vertexIndex];

		for (size_t i = 0; i < MaxBoneWightsPerVertex; i++) {
			if (boneWeights.weight[i] == 0.0f) {
				boneWeights.boneIndex[i] = boneIndex;
				boneWeights.weight[i] = weight;

				return true;
			}
		}

		return false;
	}

	Bone* Skeleton::GetBoneByName(const rString& name) {
		auto result = _impl->bonesByName.find(name);

		if (result == _impl->bonesByName.end())
			return nullptr;
		else
			return result->second;
	}

	Bone* Skeleton::GetBone(uint32_t id) const{
		if (id < _impl->bones.size())
			return _impl->bones[id].get();
		else
			return nullptr;
	}

	size_t Skeleton::GetBoneCount() const {
		return _impl->bones.size();
	}

	size_t Skeleton::GetMaxBoneWeightsPerVertex() const {
		return MaxBoneWightsPerVertex;
	}

	size_t Skeleton::GetNumVertexBoneWeights() const {
		return _impl->vertexBoneWeights.size();
	}

	size_t Skeleton::GetVertexBoneWeightsDataSize() const {
		return _impl->vertexBoneWeights.size() * sizeof(VertexBoneWeights);
	}

	const char* Skeleton::GetVertexBoneWeightData() const {
		return (const char*)_impl->vertexBoneWeights.data();
	}

	void Skeleton::SetGlobalSkeletonTransform(const rMatrix4& matrix) {
		_impl->globalTransform = matrix;
	}

	void Skeleton::Impl::InitHeader(SkeletonFileHeader& header) {
		header.numBones = bones.size();
		header.numAnimations = animations.size();
		header.numVertexBoneWeights = vertexBoneWeights.size();
	}

	rMatrix4 Skeleton::GetGlobalTransform(const Bone* bone) const {
		if (bone->IsRoot()) {
			return bone->transform;
		}
		else {
			rMatrix4 globalTransform = bone->transform;

			do {
				bone = GetBone(bone->parentId);
				globalTransform = globalTransform * bone->transform;
			} while (!bone->IsRoot());

			return globalTransform;
		}
		
	}

	Animation* Skeleton::CreateAnimation(const rString& name) {
		if (_impl->animationsByName.count(name)) {
			return nullptr;
		}
		else {
			Animation* animation = new Animation(name, _impl->animations.size());
			_impl->animations.emplace_back(animation);
			_impl->animationsByName[name] = animation;

			return animation;
		}
	}

	Animation* Skeleton::GetAnimationByName(const rString& name) {
		auto result = _impl->animationsByName.find(name);

		if (result == _impl->animationsByName.end())
			return nullptr;
		else
			return result->second;
	}

	Animation* Skeleton::GetAnimation(size_t id) {
		return _impl->animations[id].get();
	}

	size_t Skeleton::NumAnimations() const {
		return _impl->animations.size();
	}

	void WriteString(const rString& str, rOStream& stream) {
		uint32_t strSize = str.size();
		stream.Write((const char*)&strSize, sizeof(uint32_t));
		stream.Write(str.c_str(), strSize);
	}

	int Skeleton::Write(rOStream& stream) {

		SkeletonFileHeader header;
		_impl->InitHeader(header);
		stream.Write((const char *)&header, sizeof(SkeletonFileHeader));

		for (size_t i = 0; i < _impl->bones.size(); i++) {
			Bone* boneData = _impl->bones[i].get();
			WriteString(boneData->name, stream);

			stream.Write((const char*)&boneData->parentId, sizeof(uint32_t));
			stream.Write((const char*)&boneData->transform.m, sizeof(float) * 16);
		}

		for (size_t i = 0; i < _impl->animations.size(); i++) {
			Animation* animation = _impl->animations[i].get();

			rString animName = animation->Name();
			WriteString(animName, stream);
		}

		uint32_t vertexBoneWeightSize = _impl->vertexBoneWeights.size();
		stream.Write((const char*)&vertexBoneWeightSize, sizeof(uint32_t));
		stream.Write(GetVertexBoneWeightData(), GetVertexBoneWeightsDataSize());

		return 0;
	}

	rString ReadName(rIStream& stream) {
		uint32_t nameSize;
		stream.Read((char*)&nameSize, sizeof(uint32_t));
		std::vector<char> nameBuffer(nameSize);
		stream.Read(nameBuffer.data(), nameSize);
		rString nameStr(nameBuffer.data(), nameSize);

		return nameStr;
	}

	int Skeleton::Read(rIStream& stream) {
		SkeletonFileHeader header;
		stream.Read((char *)&header, sizeof(SkeletonFileHeader));

		for (uint32_t i = 0; i < header.numBones; i++) {
			rString boneName = ReadName(stream);
			Bone* boneData = CreateBone(boneName);

			stream.Read((char*)&boneData->parentId, sizeof(uint32_t));
			stream.Read((char*)&boneData->transform.m, sizeof(float) * 16);
		}

		for (uint32_t i = 0; i < header.numAnimations; i++) {
			rString animName = ReadName(stream);
			Animation* animation = CreateAnimation(animName);
		}

		uint32_t vertexBoneWeightSize;
		stream.Read((char*)&vertexBoneWeightSize, sizeof(uint32_t));
		_impl->vertexBoneWeights.resize(vertexBoneWeightSize);
		stream.Read((char*)_impl->vertexBoneWeights.data(), GetVertexBoneWeightsDataSize());

		return 0;
	}
}

