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
	virtual void AfterUpdateScene();

	virtual void AfterRenderScene(rViewport* viewport);
	virtual void BeforeRenderUi(rViewport* viewport);

private:
	rViewport* CreateView(Model* model, rEngine* engine);
	bool ParseArgs(const rArrayString& args, rString& file, rString& archive);

private:
	rEngine* _engine;

	std::unique_ptr<ModelViewerCamera> _demoCamera;
	std::unique_ptr<SkeletonGeometry> _skeletonGeometry;
};