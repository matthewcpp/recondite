#include "rAnimation.hpp"

namespace recondite{

	Animation::Animation(const rString& name, uint32_t id) {
		_name = name;
		_id = id;
	}

	BoneAnimation* Animation::CreateBoneAnimation(uint32_t id) {
		if (_boneAnimations.count(id)) {
			return nullptr;
		}
		else {
			BoneAnimation* boneAnimation = new BoneAnimation(id);
			_boneAnimations.emplace(id, boneAnimation);

			return boneAnimation;
		}
	}

	BoneAnimation* Animation::GetBoneAnimation(uint32_t id) {
		auto result = _boneAnimations.find(id);

		if (result == _boneAnimations.end()) {
			return nullptr;
		}
		else {
			return result->second.get();
		}
	}
}
