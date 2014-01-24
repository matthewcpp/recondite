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

class rDemoModule : public rModule{
public:

	virtual void Update(rEngine& engine);
	virtual void Draw(rEngine& engine);
	virtual void Init(rEngine& engine);
	virtual void Uninit(rEngine& engine);

	virtual void InitUI(ruiLayoutManager& uiManager, rEngine& engine);

private:
	void InitView(rEngine& engine);
	void LoadContent(rEngine& engine);
	void LoadUi(rEngine& engine);

private:
	rViewport m_viewport;
	rViewCamera* m_camera;
	rPawn* m_pawn;

	ruiDemoController* m_controller;
};

#endif