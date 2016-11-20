#pragma once

#include <vector>

#include "rBuild.hpp"
#include "rSkeleton.hpp"
#include "rTime.hpp"

namespace recondite {
	class RECONDITE_API AnimationController {
	public:
		AnimationController();

	public:

		/**
		Updates the animation
		\param time Time information from engine
		*/
		void Update(const rTime& time);

		/**
		Sets the skeleton to use with this Controller
		\param skeleton the skeleton that will be used with this controller
		*/
		void SetSkeleton(Skeleton* skeleton);

		/**
		Sets the active animation that will be played.  Current Animaiton time is reset to 0 if a valid animation is set.
		\param name the name of the animation to activate. If an invalid animation is specified no action is taken.
		\returns value indicating if the animation was sucessfully activated
		*/
		bool SetAnimation(const rString& name);

		/**
		Indicates if an animation is currently playing
		\returns boolean value indicating if an animation is currently active
		*/
		inline bool IsPlaying() const;

		/**
		Pauses animation playback. Animation progress is preserved.
		*/
		inline void Pause();

		/**
		Starts animation playback
		*/
		void Play();

		/**
		Stops all animation playback and resets time to 0
		*/
		void Stop();

		/**
		Sets wheter the active animation should loop.
		\param loop value indicating wheter animation should loop
		*/
		inline void SetLoop(bool loop);

		/**
		Gets wheter the active animation will loop when the end is reached.  Default value is false.
		\returns boolean value indicating wheter the current animation will loop
		*/
		inline bool GetLoop() const;

		/**
		Sets speed modidifer for the animation
		\param speed animation speed multiple
		*/
		inline void SetSpeed(float speed);

		/**
		Gets speed modifier for the animation.  Default value is 1.0
		\returns speed modifier for the animation
		*/
		inline float GetSpeed() const;

		/**
		Gets currently active animation
		\returns active animation.
		*/
		inline Animation* GetAnimation() const;

		/**
		Gets the current animation progress
		\returns current animation progress
		*/
		inline float GetAnimationTime() const;

		/**
		Sets the current animation progress
		\param time the new animation progress
		*/
		void SetAnimationTime(float time);

		/**
		Gets the current transform matrices for this controller
		\returns current state of transformed matrices
		*/
		inline const rMatrix4* GetBoneTransformData() const;

		/**
		Gets the number of matrices returned by GetBoneTransformData()
		\returns the matrix count
		*/
		inline size_t GetBoneTransformCount() const;

	private:

		rVector3 InterpolateTranslate(float time, const AnimationChannel* animationChannel);
		rVector3 InterpolateScale(float time, const AnimationChannel* animationChannel);
		rQuaternion InterpolateRotation(float time, const AnimationChannel* animationChannel);

		void Reset();

		void CalculateBoneTransform(uint32_t boneId, const rMatrix4& parentTransform);

	private:
		Skeleton* _skeleton;
		std::vector<rMatrix4> _boneTransforms;
		bool _isPlaying;
		float _animationSpeed;
		float _animationTime;
		bool _loop;
		Animation* _animation;
	};

	inline bool AnimationController::IsPlaying() const {
		return _isPlaying;
	}

	inline void AnimationController::Pause() {
		_isPlaying = false;
	}

	inline void AnimationController::SetSpeed(float speed) {
		_animationSpeed = speed;
	}

	inline float AnimationController::GetSpeed() const {
		return _animationSpeed;
	}

	inline Animation* AnimationController::GetAnimation() const {
		return _animation;
	}

	inline float AnimationController::GetAnimationTime() const {
		return _animationTime;
	}

	inline const rMatrix4* AnimationController::GetBoneTransformData() const {
		return _boneTransforms.data();
	}

	inline size_t AnimationController::GetBoneTransformCount() const {
		return _boneTransforms.size();
	}

	inline void AnimationController::SetLoop(bool loop) {
		_loop = loop;
	}

	inline bool AnimationController::GetLoop() const {
		return _loop;
	}
}