#ifndef RUI_DEMOCONTROLLER_HPP
#define RUI_DEMOCONTROLLER_HPP

#include "ui/ruiBase.hpp"

#include "ui/ruiDPad.hpp"
#include "ui/ruiPicker.hpp"
#include "ui/ruiSlider.hpp"
#include "ui/ruiButton.hpp"
#include "ui/ruiCheckbox.hpp"
#include "ui/ruiLayoutManager.hpp"
#include "ui/ruiText.hpp"

#include "input/rController.hpp"
#include "rContentManager.hpp"

#include "rEngine.hpp"
#include "rPawn.hpp"

#include "rLog.hpp"

class ruiDemoController : public ruiController {
public:
	ruiDemoController(rContentManager* contentManager, rController* controller);
	~ruiDemoController();

	virtual void Init(ruiOverlay* overlay);

	void OnUpdate(rEngine& engine);
	void OnDraw(rEngine& engine);

	void OnModelChange(ruiWidget* widget);
	void OnAnimationChange(ruiWidget* widget);

private:
	void SetActiveModel(const rString& name);

private:
	rController* m_controller;
	rContentManager* m_contentManager;

	ruiPicker* m_modelPicker;
	ruiPicker* m_animationPicker;

	rPawn* m_pawn;
};

#endif
