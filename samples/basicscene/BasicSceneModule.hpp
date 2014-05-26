#ifndef BASICSCENEMODULE_HPP
#define BASICSCENEMODULE_HPP

#include "rModule.hpp"

#include "rCamera.hpp"

class BasicSceneModule : public rModule{
public:

	virtual void Update(rEngine& engine);
	virtual void Draw(rEngine& engine);
	virtual void Init(rEngine& engine);
	virtual void InitUI(ruiOverlayManager& manager, rEngine& engine);
	virtual void Uninit(rEngine& engine);
	virtual void LoadScene(const rString& sceneName, rEngine& engine);
	virtual void DeleteActor(rActor3* actor);

};

#endif