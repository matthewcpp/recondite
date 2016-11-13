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
	struct RECONDITE_API BoneAnimation {
		BoneAnimation(uint32_t _id) : id(_id) {}

		struct VectorKey {
			VectorKey() : time(0.0f), value(rVector3::ZeroVector) {}
			VectorKey(float t, float x, float y, float z) : time(t), value(x,y,z) {}

			float time;
			rVector3 value;
		};

		struct QuaternionKey {
			QuaternionKey() : time(0.0f), value(rQuaternion::Identity) {}
			QuaternionKey(float t, float x, float y, float z, float w) : time(t), value(x,y,z,w) {}

			float time;
			rQuaternion value;
		};

		uint32_t id;

		std::vector<VectorKey> translationKeys;
		std::vector<VectorKey> scaleKeys;
		std::vector<QuaternionKey> rotationKeys;
	};

	class RECONDITE_API Animation {
	public:
		Animation(const rString& name, uint32_t id);

	public:
		inline rString Name() const;
		inline uint32_t Id() const;

		BoneAnimation* CreateBoneAnimation(uint32_t id);
		BoneAnimation* GetBoneAnimation(uint32_t id);

	private:
		rString _name;
		uint32_t _id;

		std::map<uint32_t, std::unique_ptr<BoneAnimation>> _boneAnimations;

		rNO_COPY_CLASS(Animation)
	};

	inline rString Animation::Name() const {
		return _name;
	}

	inline uint32_t Animation::Id() const {
		return _id;
	}
}

