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

#include "rLog.hpp"

class ruiDemoController : public ruiController {
public:
	ruiDemoController(rContentManager* contentManager, rController* controller);
	virtual void Init(ruiOverlay* overlay);

	void OnModelChange(ruiWidget* widget);

	rString GetActiveModelName();

private:
	void SetActiveModel(const rString& name);

private:
	rController* m_controller;
	rContentManager* m_contentManager;

	rString m_activeModelName;

	ruiPicker* m_modelPicker;
	ruiPicker* m_animationPicker;
};

#endif
