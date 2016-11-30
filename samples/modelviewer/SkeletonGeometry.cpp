#include "SkeletonGeometry.hpp"

SkeletonGeometry::SkeletonGeometry(rEngine* engine, rPawn* pawn) {
	_engine = engine;
	_pawn = pawn;

	_renderBones = false;
	_renderBoneNames = false;

	_boneColor = rColor::Green;
	_labelColor = rColor::White;

	Init();
}

void SkeletonGeometry::Init() {
	recondite::Skeleton* skeleton = _pawn->GetModel()->GetSkeleton();

	_skeletonBuffer.Reset(rGeometryType::Lines, 3, false);
	_skeletonWorldPoints.resize(skeleton->GetBoneCount());
	_skeletonTransformedPoints.resize(skeleton->GetBoneCount());

	for (size_t i = 0; i < skeleton->GetBoneCount(); i++) {
		recondite::Bone* bone = skeleton->GetBone(i);
		_skeletonWorldPoints[i] = skeleton->GetGlobalTransform(bone).GetTranslate();
	}
}

void SkeletonGeometry::Update() {
	if (_renderBones) {
		Skeleton* skeleton = _pawn->GetModel()->GetSkeleton();
		const rMatrix4* boneTransforms = _pawn->AnimationController()->GetBoneTransformData();

		_skeletonBuffer.Clear();
		GenerateCurrentSkeletonBuffer(skeleton->GetRootBone()->id, skeleton, boneTransforms);
	}
}

void SkeletonGeometry::DrawSkeleton() {
	if (_renderBones) {
		_engine->renderer->EnableDepthTesting(false);
		_engine->renderer->RenderImmediateLines(_skeletonBuffer, _boneColor);
		_engine->renderer->EnableDepthTesting(true);
	}
}

void SkeletonGeometry::DrawLabels(rViewport* viewport) {
	if (_renderBones && _renderBoneNames) {
		rRect screenRect = viewport->GetScreenRect();

		rMatrix4 viewMatrix, projectionMatrix;
		viewport->GetViewMatrix(viewMatrix);
		viewport->GetProjectionMatrix(projectionMatrix);

		rSpriteBatch* sb = _engine->renderer->SpriteBatch();

		Skeleton* skeleton = _pawn->GetModel()->GetSkeleton();

		for (size_t i = 0; i < skeleton->GetBoneCount(); i++) {
			Bone* bone = skeleton->GetBone(i);

			rVector2 projectedPoint;
			rMatrixUtil::Project(_skeletonTransformedPoints[bone->id], viewMatrix, projectionMatrix, screenRect, projectedPoint);
			projectedPoint.y = float(screenRect.height) - projectedPoint.y;

			sb->RenderString(bone->name, _engine->content->Fonts()->SystemDefault(), rPoint(projectedPoint.x, projectedPoint.y), _labelColor);
		}
	}
}

void SkeletonGeometry::GenerateCurrentSkeletonBuffer(uint32_t boneId, Skeleton* skeleton, const rMatrix4* boneTransforms) {
	Bone* bone = skeleton->GetBone(boneId);

	const rMatrix4* matrix = boneTransforms + boneId;
	_skeletonTransformedPoints[boneId] = matrix->GetTransformedVector3(_skeletonWorldPoints[boneId]);

	if (!bone->IsRoot()) {
		_skeletonBuffer.PushIndex(_skeletonBuffer.VertexCount(), _skeletonBuffer.VertexCount() + 1);

		_skeletonBuffer.PushVertex(_skeletonTransformedPoints[boneId]);
		_skeletonBuffer.PushVertex(_skeletonTransformedPoints[bone->parentId]);
	}

	for (size_t i = 0; i < bone->children.size(); i++) {
		GenerateCurrentSkeletonBuffer(bone->children[i], skeleton, boneTransforms);
	}

}