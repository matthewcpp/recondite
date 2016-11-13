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
		size_t GetBoneCount() const;

		void AllocateVertexWeightData(size_t numVertices);
		bool AddVertexWeight(size_t vertexIndex, size_t boneIndex, float weight);
		size_t GetNumVertexBoneWeights() const;
		size_t GetVertexBoneWeightsDataSize() const;
		const char* GetVertexBoneWeightData() const;

		void SetGlobalSkeletonTransform(const rMatrix4& matrix);

		size_t GetMaxBoneWeightsPerVertex() const;

		rMatrix4 GetGlobalTransform(const Bone* bone) const;

		int Write(rOStream& stream);
		int Read(rIStream& stream);

		Animation* CreateAnimation(const rString& name);
		Animation* GetAnimationByName(const rString& name);
		Animation* GetAnimation(size_t id);
		size_t NumAnimations() const;
	private:
		struct Impl;
		Impl* _impl;
	};
}
