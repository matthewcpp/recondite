#ifndef BASICSCENEMODULE_HPP
#define BASICSCENEMODULE_HPP

#include "rModule.hpp"

#include "rCamera.hpp"

#include "ui/ruiText.hpp"
#include "ui/ruiButton.hpp"
#include "stream/rOStringStream.hpp"

#include "primitive/rPrimitiveBox.hpp"

class BasicSceneModule : public rModule{
public:

	virtual void BeforeUpdateScene(rEngine& engine);
	virtual void AfterUpdateScene(rEngine& engine);

	virtual void BeforeRenderScene(rViewInfo& view, rEngine& engine);
	virtual void AfterRenderScene(rViewInfo& view, rEngine& engine);

	virtual void BeforeRenderOverlay(rViewInfo& view, rEngine& engine);
	virtual void AfterRenderOverlay(rViewInfo& view, rEngine& engine);

	virtual void Init(rEngine& engine);
	virtual void InitUI(ruiOverlayManager& manager, rEngine& engine);
	virtual void Uninit(rEngine& engine);
	virtual void LoadScene(const rString& sceneName, rEngine& engine);
	virtual void DeleteActor(rActor3* actor);

private:
	ruiText* m_textCameraPos;
	rViewCamera* m_camera;

private:
		

};

#endif