#pragma once

#include <vector>

#include "rModule.hpp"
#include "ModelViewerSettings.hpp"

class ModelViewerModule : public rModule {
public:
	ModelViewerModule(rEngine* engine);

	virtual void Init(const rArrayString& args);
	virtual void LoadScene(const rString& sceneName) override;
	virtual void DeleteActor(rActor3* actor) override;

	virtual void AfterRenderScene(rViewport* viewport);
	virtual void BeforeRenderUi(rViewport* viewport);

private:
	void CreateSkeletonGeometry(recondite::ModelData& modelData);
	void GenerateCurrentSkeletonBuffer(uint32_t boneId, Skeleton* skeleton, const rMatrix4* boneTransforms);

private:
	rEngine* _engine;

	ModelViewerSettings settings;

	std::vector<rVector3> skeletonWorldPoints;
	std::vector<rVector3> skeletonTransformedPoints;
	rImmediateBuffer skeletonBuffer;

};