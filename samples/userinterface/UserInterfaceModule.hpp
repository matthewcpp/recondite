#pragma once

#pragma once

#include "rModule.hpp"

class UserInterfaceModule : public rModule{
public:
	UserInterfaceModule(rEngine* engine);

	virtual void Init();
	virtual void LoadScene(const rString& sceneName) override;
	virtual void DeleteActor(rActor3* actor) override;

	virtual void AfterRenderScene(rViewport* viewport);

private:
	rEngine* _engine;
};