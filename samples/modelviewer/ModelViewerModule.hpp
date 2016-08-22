#pragma once

#include "rModule.hpp"

class ModelViewerModule : public rModule {
public:
	ModelViewerModule(rEngine* engine);

	virtual void Init(const rArrayString& args);
	virtual void LoadScene(const rString& sceneName) override;
	virtual void DeleteActor(rActor3* actor) override;

	virtual void AfterRenderScene(rViewport* viewport);

private:
	rEngine* _engine;
};