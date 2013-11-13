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

#include "rLog.hpp"

class ruiDemoController : public ruiController {
public:
	ruiDemoController(rController* controller);
	virtual void Init(ruiOverlay* overlay);

	void OnPickerChange(ruiWidget* button);
	void OnSliderChange(ruiWidget* slider);
	void OnCheckboxChange(ruiWidget* checkbox);
	void OnButtonClick(ruiWidget* button);

private:
	rController* m_controller;

	ruiPicker* m_picker;
	ruiSlider* m_slider;
	ruiCheckbox* m_checkbox;
	ruiButton* m_button;
};

#endif
