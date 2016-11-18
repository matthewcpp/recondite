#include "rSkeleton.hpp"

#include <map>
#include <memory>

namespace recondite {
#define RootBoneId UINT32_MAX

	bool Bone::IsRoot() const {
		return parentId == RootBoneId;
	}

	struct SkeletonFileHeader {
		uint32_t numBones;
		uint32_t numAnimations;
	};

	struct Skeleton::Impl {
		std::vector <std::unique_ptr<Bone>> bones;
		uint32_t rootBone;
		std::map<rString, Bone*> bonesByName;

		std::vector <std::unique_ptr<Animation>> animations;
		std::map<rString, Animation*> animationsByName;

		rMatrix4 globalTransform;

		void InitHeader(SkeletonFileHeader& header);

		Impl():rootBone(RootBoneId) {}
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

	void Skeleton::SetGlobalSkeletonTransform(const rMatrix4& matrix) {
		_impl->globalTransform = matrix;
	}

	void Skeleton::Impl::InitHeader(SkeletonFileHeader& header) {
		header.numBones = bones.size();
		header.numAnimations = animations.size();
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

	void Skeleton::CacheBoneData() {
		for (size_t i = 0; i < _impl->bones.size(); i++) {
			Bone* bone = _impl->bones[i].get();

			bone->invWorldTransform = GetGlobalTransform(bone);
			bone->invWorldTransform.Invert();

			if (bone->IsRoot())
				_impl->rootBone = bone->id;
		}
	}

	Bone* Skeleton::GetRootBone() {
		if (_impl->rootBone == RootBoneId) //root is unset
			return nullptr;
		else
			return _impl->bones[_impl->rootBone].get();
	}

	Animation* Skeleton::CreateAnimation(const rString& name, float duration) {
		if (_impl->animationsByName.count(name)) {
			return nullptr;
		}
		else {
			Animation* animation = new Animation(name, duration, _impl->animations.size());
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

	size_t Skeleton::GetAnimationCount() const {
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

		stream.Write((const char *)&_impl->rootBone, sizeof(uint32_t));

		for (size_t i = 0; i < _impl->bones.size(); i++) {
			Bone* boneData = _impl->bones[i].get();
			WriteString(boneData->name, stream);

			stream.Write((const char*)&boneData->parentId, sizeof(uint32_t));

			uint32_t childCount = boneData->children.size();
			stream.Write((const char*)&childCount, sizeof(uint32_t));

			if (childCount > 0) {
				stream.Write((const char*)boneData->children.data(), sizeof(uint32_t) * childCount);
			}

			stream.Write((const char*)&boneData->transform.m, sizeof(rMatrix4));
			stream.Write((const char*)&boneData->invWorldTransform.m, sizeof(rMatrix4));
		}

		for (size_t i = 0; i < _impl->animations.size(); i++) {
			Animation* animation = _impl->animations[i].get();

			rString animName = animation->Name();
			WriteString(animName, stream);

			float duration = animation->Duration();
			stream.Write((const char*)&duration, sizeof(float));

			uint32_t channelCount = animation->GetChannelCount();
			stream.Write((const char*)&channelCount, sizeof(uint32_t));

			for (size_t i = 0; i < channelCount; i++) {
				AnimationChannel* channel = animation->GetChannelByIndex(i);

				stream.Write((const char*)&channel->boneId, sizeof(uint32_t));

				uint32_t count = channel->translationKeys.times.size();
				stream.Write((const char*)&count, sizeof(uint32_t));
				if (count > 0) {
					stream.Write((const char*)channel->translationKeys.times.data(), sizeof(float) * count);
					stream.Write((const char*)channel->translationKeys.values.data(), sizeof(rVector3) * count);
				}

				count = channel->scaleKeys.times.size();
				stream.Write((const char*)&count, sizeof(uint32_t));
				if (count > 0) {
					stream.Write((const char*)channel->scaleKeys.times.data(), sizeof(float) * count);
					stream.Write((const char*)channel->scaleKeys.values.data(), sizeof(rVector3) * count);
				}
				
				count = channel->rotationKeys.times.size();
				stream.Write((const char*)&count, sizeof(uint32_t));
				if (count > 0) {
					stream.Write((const char*)channel->rotationKeys.times.data(), sizeof(float) * count);
					stream.Write((const char*)channel->rotationKeys.values.data(), sizeof(rQuaternion) * count);
				}
			}
		}

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

		stream.Read((char *)&_impl->rootBone, sizeof(uint32_t));

		for (uint32_t i = 0; i < header.numBones; i++) {
			rString boneName = ReadName(stream);
			Bone* boneData = CreateBone(boneName);

			stream.Read((char*)&boneData->parentId, sizeof(uint32_t));

			uint32_t childCount;
			stream.Read((char*)&childCount, sizeof(uint32_t));
			if (childCount > 0) {
				boneData->children.resize(childCount);
				stream.Read((char*)boneData->children.data(), sizeof(uint32_t) * childCount);
			}

			stream.Read((char*)&boneData->transform.m, sizeof(rMatrix4));
			stream.Read((char*)&boneData->invWorldTransform.m, sizeof(rMatrix4));
		}

		for (uint32_t i = 0; i < header.numAnimations; i++) {
			rString animName = ReadName(stream);
			float duration;
			stream.Read((char*)&duration, sizeof(float));
			Animation* animation = CreateAnimation(animName, duration);

			uint32_t channelCount;
			stream.Read((char*)&channelCount, sizeof(uint32_t));

			for (uint32_t i = 0; i < channelCount; i++) {
				uint32_t boneId;
				stream.Read((char*)&boneId, sizeof(uint32_t));
				AnimationChannel* channel = animation->CreateChannelForBone(boneId);

				uint32_t count;
				stream.Read((char*)&count, sizeof(uint32_t));

				if (count > 0) {
					channel->translationKeys.times.resize(count);
					channel->translationKeys.values.resize(count);
					stream.Read((char*)channel->translationKeys.times.data(), sizeof(float) * count);
					stream.Read((char*)channel->translationKeys.values.data(), sizeof(rVector3) * count);
				}
			
				stream.Read((char*)&count, sizeof(uint32_t));
				if (count > 0) {
					channel->scaleKeys.times.resize(count);
					channel->scaleKeys.values.resize(count);
					stream.Read((char*)channel->scaleKeys.times.data(), sizeof(float) * count);
					stream.Read((char*)channel->scaleKeys.values.data(), sizeof(rVector3) * count);
				}

				stream.Read((char*)&count, sizeof(uint32_t));
				if (count > 0) {
					channel->rotationKeys.times.resize(count);
					channel->rotationKeys.values.resize(count);
					stream.Read((char*)channel->rotationKeys.times.data(), sizeof(float) * count);
					stream.Read((char*)channel->rotationKeys.values.data(), sizeof(rQuaternion) * count);
				}
			}
		}

		return 0;
	}
}

