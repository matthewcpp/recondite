#ifndef R_DEMOMODULE_HPP
#define R_DEMOMODULE_HPP


#include "rViewport.hpp"
#include "rCamera.hpp"
#include "rPawn.hpp"

#include "rLog.hpp"

#include "rModule.hpp"

#include "ui/ruiPicker.hpp"
#include "ui/ruiOverlay.hpp"

#include "ruiDemoController.hpp"
#include "rDemoCamera.hpp"

#include "data/rLogContentListener.hpp"

class rDemoModule : public rModule{
public:

	virtual void BeforeUpdateScene(rEngine& engine);
	virtual void AfterUpdateScene(rEngine& engine);

	virtual void BeforeRenderScene(rViewInfo& view, rEngine& engine);
	virtual void AfterRenderScene(rViewInfo& view, rEngine& engine);

	virtual void BeforeRenderOverlay(rViewInfo& view, rEngine& engine);
	virtual void AfterRenderOverlay(rViewInfo& view, rEngine& engine);


	virtual void Init(rEngine& engine);
	virtual void Uninit(rEngine& engine);

	virtual void InitUI(ruiOverlayManager& uiManager, rEngine& engine);
	virtual void LoadScene(const rString& sceneName, rEngine& engine);
	virtual void DeleteActor(rActor3* actor);

private:
	void InitView(rEngine& engine);
	void LoadContent(rEngine& engine);
	void LoadUi(rEngine& engine);

private:
	rViewport* m_viewport;
	rDemoCamera* m_camera;
	rDemoPawn* m_pawn;

	ruiDemoController* m_controller;
};

#endif
