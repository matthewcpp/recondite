#include "UserInterfaceController.hpp"
#include "ui/ruiWidget.hpp"
#include "ui/ruiEvents.hpp"
#include "ui/ruiCheckbox.hpp"
#include "ui/ruiSlider.hpp"
#include "rActor3.hpp"

UserInterfaceController::UserInterfaceController(const rString& name, rEngine* engine, ruiDocument* document)
	:ruiController(name)
{
	_engine = engine;
	_document = document;
	_rotateHandle = 0;
	_rotationSpeed = 10.0f;
}

void UserInterfaceController::OnRotateCheckboxClick(rEvent& event){
	ruiWidgetEvent& widgetEvent = (ruiWidgetEvent&)event;
	ruiCheckbox* checkbox = (ruiCheckbox*)widgetEvent.Widget();

	if (checkbox->IsChecked()){
		_rotateHandle = _document->RunEveryUpdate([&](){
			rActor3* actor = _engine->scene->GetActor("box");
			rVector3 rotation = actor->Rotation();
			rotation.y += _rotationSpeed * +_engine->time.TimeDeltaSeconds();
			actor->SetRotation(rotation);
		});
	}
	else{
		_document->ClearRunEveryUpdate(_rotateHandle);
	}
}

void UserInterfaceController::OnRotationSpeedSliderChange(rEvent& event){
	ruiWidgetEvent& widgetEvent = (ruiWidgetEvent&)event;

	ruiSlider* slider = (ruiSlider*)widgetEvent.Widget();
	_rotationSpeed = slider->GetValue();
}

void UserInterfaceController::OnDocumentLoaded(){
	ruiWidget* rotate_checkbox = _document->GetWidget("rotate_checkbox");
	rotate_checkbox->Bind(ruiEVENT_CHECKBOX_CHANGE, this, &UserInterfaceController::OnRotateCheckboxClick);

	ruiSlider* rotate_speed = (ruiSlider*)_document->GetWidget("rotate_speed");
	rotate_speed->Bind(ruiEVENT_SLIDER_CHANGE, this, &UserInterfaceController::OnRotationSpeedSliderChange);
}