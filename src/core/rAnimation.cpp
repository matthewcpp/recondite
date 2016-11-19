#include "rAnimation.hpp"

namespace recondite{

	Animation::Animation(const rString& name, float duration, uint32_t id) {
		_name = name;
		_id = id;
		_duration = duration;
	}

	AnimationChannel* Animation::CreateChannelForBone(uint32_t boneId) {
		if (_boneChannelMap.count(boneId)) {
			return nullptr;
		}
		else {
			AnimationChannel* boneAnimation = new AnimationChannel(boneId, _animationChannels.size());
			_animationChannels.emplace_back(boneAnimation);
			_boneChannelMap[boneId] = boneAnimation;

			return boneAnimation;
		}
	}

	AnimationChannel* Animation::GetChannelForBone(uint32_t id) {
		auto result = _boneChannelMap.find(id);

		if (result == _boneChannelMap.end()) {
			return nullptr;
		}
		else {
			return result->second;
		}
	}

	AnimationChannel* Animation::GetChannelByIndex(size_t index) {
		return _animationChannels[index].get();
	}

	size_t Animation::GetChannelCount() const {
		return _animationChannels.size();
	}
}
