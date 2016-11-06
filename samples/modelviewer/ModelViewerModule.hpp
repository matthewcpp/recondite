#pragma once

#include <map>

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

private:
	rEngine* _engine;

	ModelViewerSettings settings;

	std::map<rString, rVector3> boneLabelPoints;
	rImmediateBuffer skeletonBuffer;

};