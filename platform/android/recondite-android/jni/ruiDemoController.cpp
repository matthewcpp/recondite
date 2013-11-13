#include "ruiDemoController.hpp"

ruiDemoController::ruiDemoController(rController* controller){
	m_controller = controller;
}

void ruiDemoController::Init(ruiOverlay* overlay){
	overlay->AddWidget(new ruiDPad(m_controller->DPad(0), 100, rPoint(700, 300), rSize(300, 300)));
	overlay->AddWidget(new ruiPicker(102, rPoint(25,10), rSize(250, 35)));
	overlay->AddWidget(new ruiSlider(101, rPoint(25,75), rSize(250, 35)));
	overlay->AddWidget(new ruiButton("click me", 666, rPoint(25, 120), rSize(175, 40)));
	overlay->AddWidget(new ruiCheckbox(667, rPoint(25, 195), rSize(50, 50)));
	overlay->AddWidget(new ruiText("Hello Android, How R U?\nDroid Does.", 900, rPoint(25, 275), rSize(200, 150)));
}
