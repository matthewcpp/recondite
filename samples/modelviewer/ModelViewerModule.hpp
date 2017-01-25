#pragma once

#include <vector>
#include <memory>

#include "rModule.hpp"
#include "ModelViewerCamera.hpp"
#include "SkeletonGeometry.hpp"

class ModelViewerModule : public recondite::Module {
public:
	ModelViewerModule(rEngine* engine);

	virtual void Init(const rArrayString& args);
	virtual void LoadScene(const rString& sceneName) override;
	virtual void DeleteActor(rActor3* actor) override;
	virtual void AfterUpdateScene();

	virtual void AfterRenderScene(rViewport* viewport);
	virtual void BeforeRenderUi(rViewport* viewport);

private:
	rViewport* CreateView(Model* model, rEngine* engine);

private:
	rEngine* _engine;

	std::unique_ptr<ModelViewerCamera> _demoCamera;
	std::unique_ptr<SkeletonGeometry> _skeletonGeometry;
};