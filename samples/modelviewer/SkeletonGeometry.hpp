#pragma once

#include <vector>

#include "rEngine.hpp"
#include "rSkeleton.hpp"
#include "rVector3.hpp"
#include "rPawn.hpp"

class SkeletonGeometry {
public:
	SkeletonGeometry(rEngine* engine, rPawn* pawn);

public:
	void Update();
	void DrawSkeleton();
	void DrawLabels(rViewport* viewport);

public:
	inline void SetRenderBones(bool renderBones);
	inline void SetRenderBoneNames(bool renderBoneNames);

	inline bool GetRenderBones() const;
	inline bool GetRenderBoneNames() const;

private:
	void Init();
	void GenerateCurrentSkeletonBuffer(uint32_t boneId, Skeleton* skeleton, const rMatrix4* boneTransforms);

private:
	rPawn* _pawn;
	rEngine* _engine;

	bool _renderBones;
	bool _renderBoneNames;

	std::vector<rVector3> _skeletonWorldPoints;
	std::vector<rVector3> _skeletonTransformedPoints;
	rImmediateBuffer _skeletonBuffer;

	rColor _boneColor;
	rColor _labelColor;
};

inline void SkeletonGeometry::SetRenderBones(bool renderBones) {
	_renderBones = renderBones;
}

inline bool SkeletonGeometry::GetRenderBones() const {
	return _renderBones;
}

inline void SkeletonGeometry::SetRenderBoneNames(bool renderBoneNames) {
	_renderBoneNames = renderBoneNames;
}

inline bool SkeletonGeometry::GetRenderBoneNames() const {
	return _renderBoneNames;
}