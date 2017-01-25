#pragma once

#include "rModule.hpp"

class UserInterfaceModule : public recondite::Module{
public:
	UserInterfaceModule(rEngine* engine);

	virtual void Init(const rArrayString& args);
	virtual void LoadScene(const rString& sceneName) override;
	virtual void DeleteActor(rActor3* actor) override;

	virtual void AfterRenderScene(rViewport* viewport);

private:
	rEngine* _engine;
};