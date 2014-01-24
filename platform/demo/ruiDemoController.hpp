#ifndef RUI_DEMOCONTROLLER_HPP
#define RUI_DEMOCONTROLLER_HPP

#include <sstream>

#include "ui/ruiPicker.hpp"
#include "ui/ruiSlider.hpp"
#include "ui/ruiButton.hpp"
#include "ui/ruiCheckbox.hpp"
#include "ui/ruiLayoutManager.hpp"
#include "ui/ruiText.hpp"

#include "rContentManager.hpp"

#include "rEngine.hpp"
#include "rPawn.hpp"

#include "rLog.hpp"

class ruiDemoController{
public:
	ruiDemoController(rContentManager* contentManager, rPawn* pawn);
	~ruiDemoController();

	virtual void Init(ruiOverlay* overlay);

	void OnUpdate(rEngine& engine);
	void OnDraw(rEngine& engine);

	void OnModelChange(ruiWidget* widget);
	void OnAnimationChange(ruiWidget* widget);

private:
	void SetActiveModel(const rString& name);

private:
	rContentManager* m_contentManager;

	ruiPicker* m_modelPicker;
	ruiPicker* m_animationPicker;

	ruiText* m_animationTime;

	rPawn* m_pawn;
};

#endif
