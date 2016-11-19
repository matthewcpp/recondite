#include "rAnimationController.hpp"

#include "rMatrixUtil.hpp"

namespace recondite {
	AnimationController::AnimationController() {
		_skeleton = nullptr;
		Reset();
	}

	void AnimationController::Reset() {
		_isPlaying = false;
		_animationSpeed = 1.0f;
		_animationTime = 0.0f;
		_animation = nullptr;
	}

	void AnimationController::Stop() {
		_isPlaying = false;
		SetAnimationTime(0.0);

		for (size_t i = 0; i < _boneTransforms.size(); i++)
			_boneTransforms[i].LoadIdentity();
	}

	void AnimationController::Play() {
		_isPlaying = true;

		if (_animation && _animationTime == _animation->Duration()) {
			_animationTime = 0.0f;
		}
	}

	void AnimationController::SetSkeleton(Skeleton* skeleton) {
		Reset();

		_skeleton = skeleton;
		_boneTransforms.resize(skeleton->GetBoneCount());
	}

	bool AnimationController::SetAnimation(const rString& name) {
		Animation* animation = _skeleton->GetAnimationByName(name);

		if (animation) {
			Stop();
			_animation = animation;
			return true;
		}
		else {
			return false;
		}
	}

	void AnimationController::CalculateBoneTransform(uint32_t boneId, const rMatrix4& parentTransform){
		Bone* bone = _skeleton->GetBone(boneId);
		rMatrix4 transform = bone->transform;

		AnimationChannel* channel = _animation->GetChannelForBone(boneId);

		if (channel) {
			rMatrix4 rotate, translate, scale;

			rVector3 translateLerp = InterpolateTranslate(_animationTime, channel);
			rVector3 scaleLerp = InterpolateScale(_animationTime, channel);
			rQuaternion rotationSlerp = InterpolateRotation(_animationTime, channel);

			translate.SetTranslate(translateLerp);
			scale.SetScale(scaleLerp);
			rMatrixUtil::QuaterionToMatrix(rotationSlerp, rotate);

			transform = scale * rotate * translate;
		}

		rMatrix4 boneTransform = parentTransform * transform ;
		rMatrix4 globalTransform = boneTransform * bone->invWorldTransform ;

		_boneTransforms[boneId] = globalTransform;

		for (size_t i = 0; i < bone->children.size(); i++) {
			CalculateBoneTransform(bone->children[i], boneTransform);
		}
	}

	void AnimationController::Update(const rTime& time) {
		if (_isPlaying && _animation) {
			SetAnimationTime(_animationTime + time.TimeDeltaSeconds() * _animationSpeed);
		}
	}

	void AnimationController::SetAnimationTime(float time) {
		if (_animation) {
			float duration = _animation->Duration();
			float newTime = std::min(time, duration);

			if (newTime != _animationTime) {
				_animationTime = newTime;
				rMatrix4 ident;
				CalculateBoneTransform(_skeleton->GetRootBone()->id, ident);
			}
		}
	}

	size_t FindKeyframeIndex(float time, const std::vector<float>& times) {
		for (size_t i = 0; i < times.size() - 1; i++) {
			if (time < times[i + 1])
				return i;
		}

		//should not get here
		return  times.size() - 2;
	}

	rVector3 InterpolateVector(float time, const AnimationChannel::VectorKeyList& keyList) {
		if (keyList.values.size() == 1) {
			return keyList.values[0];
		}
		else {
			size_t key1 = FindKeyframeIndex(time, keyList.times);
			size_t key2 = key1 + 1;
			float timeDelta = keyList.times[key2] - keyList.times[key1];
			float factor = (time - keyList.times[key1]) / timeDelta;

			return rVector3::Lerp(keyList.values[key1], keyList.values[key2], factor);
		}
	}

	rVector3 AnimationController::InterpolateTranslate(float time, const AnimationChannel* animationChannel) {
		return InterpolateVector(time, animationChannel->translationKeys);
	}

	rVector3 AnimationController::InterpolateScale(float time, const AnimationChannel* animationChannel) {
		return InterpolateVector(time, animationChannel->scaleKeys);
	}

	rQuaternion AnimationController::InterpolateRotation(float time, const AnimationChannel* animationChannel) {
		auto& rotationKeys = animationChannel->rotationKeys;

		if (rotationKeys.values.size() == 1) {
			return rotationKeys.values[0];
		}
		else {
			size_t key1 = FindKeyframeIndex(time, rotationKeys.times);
			size_t key2 = key1 + 1;
			float timeDelta = rotationKeys.times[key2] - rotationKeys.times[key1];
			float factor = (time - rotationKeys.times[key1]) / timeDelta;

			rQuaternion result = rQuaternion::Slerp(rotationKeys.values[key1], rotationKeys.values[key2], factor);
			result.Normalize();

			return result;
		}
	}
}
