#pragma once

#include <cstdint>
#include <vector>
#include <map>
#include <memory>

#include "rBuild.hpp"
#include "rDefs.hpp"
#include "rString.hpp"

#include "rVector3.hpp"
#include "rQuaternion.hpp"

namespace recondite {
	struct RECONDITE_API AnimationChannel {
		AnimationChannel(uint32_t _boneId, uint32_t _channelId) : boneId(_boneId), channelId(_channelId) {}

		struct VectorKeyList {
			std::vector<float> times;
			std::vector<rVector3> values;
		};

		struct QuaternionKeyList {
			std::vector<float> times;
			std::vector<rQuaternion> values;
		};

		uint32_t boneId;
		uint32_t channelId;

		VectorKeyList translationKeys;
		VectorKeyList scaleKeys;
		QuaternionKeyList rotationKeys;
	};

	class RECONDITE_API Animation {
	public:
		Animation(const rString& name, float duration, uint32_t id);

	public:
		/**
		Family Friendly name for this animation
		\returns the animation's name
		*/
		inline rString Name() const;

		/**
		Identifier for this animation
		\returns the animations numerical identifier.
		*/
		inline uint32_t Id() const;

		/**
		Length of the animation
		\returns the animation length
		*/
		inline float Duration() const;

		/**
		Creates a new Animation for a given bone id.
		\param boneId the id of the bone this Animation references
		\returns new bone animation container if one does not exist for the supplied bone id or null if one already exists.
		*/
		AnimationChannel* CreateChannelForBone(uint32_t boneId);

		/**
		Gets a bone animation for a given id
		\param boneId the id of the bone to get animation for
		\returns animation for the given bone id or null if one does not exist
		*/
		AnimationChannel* GetChannelForBone(uint32_t boneId);

		/**
		Gets a bone animation by its given index in the animation collection.
		\param index index of the animation to retrieve
		\returns the bone animation for the given index
		*/
		AnimationChannel* GetChannelByIndex(size_t index);

		/**
		Gets the total number of bone animations contained in this object
		\returns bone animation count
		*/
		size_t GetChannelCount() const;

	private:
		rString _name;
		uint32_t _id;

		float _duration;

		std::vector<std::unique_ptr<AnimationChannel>> _animationChannels;
		std::map<uint32_t, AnimationChannel*> _boneChannelMap;

		rNO_COPY_CLASS(Animation)
	};

	inline rString Animation::Name() const {
		return _name;
	}

	inline uint32_t Animation::Id() const {
		return _id;
	}

	inline float Animation::Duration() const {
		return _duration;
	}
}

