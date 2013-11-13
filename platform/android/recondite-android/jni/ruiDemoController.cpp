#include "ruiDemoController.hpp"

ruiDemoController::ruiDemoController(rController* controller){
	m_controller = controller;
}

void ruiDemoController::Init(ruiOverlay* overlay){
	m_picker = new ruiPicker(102, rPoint(25,10), rSize(250, 35));
	m_picker->Bind(ruiEVENT_PICKER_CHANGE, this, &ruiDemoController::OnPickerChange);

	m_slider = new ruiSlider(101, rPoint(25,75), rSize(250, 35));
	m_slider->Bind(ruiEVENT_SLIDER_CHANGE, this, &ruiDemoController::OnSliderChange);

	m_checkbox = new ruiCheckbox(667, rPoint(25, 195), rSize(50, 50));
	m_checkbox->Bind(ruiEVENT_CHECKBOX_CHANGE, this, &ruiDemoController::OnCheckboxChange);

	m_button = new ruiButton("click me", 666, rPoint(25, 120), rSize(175, 40));
	m_button->Bind(ruiEVENT_BUTTON_CLICK, this, &ruiDemoController::OnButtonClick);

	overlay->AddWidget(new ruiDPad(m_controller->DPad(0), 100, rPoint(700, 300), rSize(300, 300)));
	overlay->AddWidget(m_picker);
	overlay->AddWidget(m_slider);
	overlay->AddWidget(m_button);
	overlay->AddWidget(m_checkbox);
	overlay->AddWidget(new ruiText("Hello Android, How R U?\nDroid Does.", 900, rPoint(25, 275), rSize(200, 150)));
}

void ruiDemoController::OnButtonClick(ruiWidget* button){
	rLog::Info("button %d clicked", button->Id());
}

void ruiDemoController::OnPickerChange(ruiWidget* picker){
	rLog::Info("picker %d changed", picker->Id());
}

void ruiDemoController::OnSliderChange(ruiWidget* slider){
	ruiSlider* s = (ruiSlider*)slider;
	rLog::Info("slider changed - value: %d", s->GetValue());
}

void ruiDemoController::OnCheckboxChange(ruiWidget* checkbox){
	rLog::Info("checkbox %d changed", checkbox->Id());
}
