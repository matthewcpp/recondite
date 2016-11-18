#pragma once

#include <map>
#include <vector>

#include "rBuild.hpp"
#include "rString.hpp"
#include "rMatrix4.hpp"

#include "rAnimation.hpp"

#include "stream/rIStream.hpp"
#include "stream/rOStream.hpp"

namespace recondite {
	struct RECONDITE_API Bone {
		uint32_t id;
		uint32_t parentId;
		rString name;
		rMatrix4 transform;
		rMatrix4 invWorldTransform;
		std::vector<uint32_t> children;

		bool IsRoot() const;
	};

	class RECONDITE_API Skeleton {
	public:
		Skeleton();
		~Skeleton();

	public:
		Bone* CreateBone(const rString& name);
		Bone* GetBoneByName(const rString& name);
		Bone* GetBone(uint32_t id) const;
		Bone* GetRootBone();
		size_t GetBoneCount() const;

		void SetGlobalSkeletonTransform(const rMatrix4& matrix);

		/**
		Gets the global object space transform for a bone.
		\param bone object to get global object space transform for.
		*/
		rMatrix4 GetGlobalTransform(const Bone* bone) const;

		/**
		This method caches certain bone information.  It is only necessary to call this method after modifying the skeleton.
		*/
		void CacheBoneData();

		int Write(rOStream& stream);
		int Read(rIStream& stream);

		Animation* CreateAnimation(const rString& name, float duration);
		Animation* GetAnimationByName(const rString& name);
		Animation* GetAnimation(size_t id);
		size_t GetAnimationCount() const;
	private:
		struct Impl;
		Impl* _impl;
	};
}
