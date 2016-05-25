#include "UserInterfaceController.hpp"
#include "ui/ruiWidget.hpp"
#include "ui/ruiEvents.hpp"
#include "ui/ruiCheckbox.hpp"
#include "ui/ruiSlider.hpp"
#include "ui/ruiPicker.hpp"
#include "ui/ruiButton.hpp"
#include "rActor3.hpp"
#include "rLog.hpp"

UserInterfaceController::UserInterfaceController(const rString& name, rEngine* engine, ruiDocument* document)
	:ruiController(name)
{
	_engine = engine;
	_document = document;
	_rotateHandle = 0;
	_rotationValue = 0.0f;
	_rotationSpeed = 10.0f;
}

void UserInterfaceController::ApplyRotation(){
	rVector3 rotation = _primitive->Rotation();
	rotation.y = _rotationValue;
	_primitive->SetRotation(rotation);
}

void UserInterfaceController::OnDocumentLoaded(){
	_primitive = (rPrimitive*)_engine->scene->GetActor("Box");
	_rotationValue = _primitive->Rotation().y;

	ruiWidget* rotate_checkbox = _document->GetWidget("rotate_checkbox");
	rotate_checkbox->Bind(ruiEVENT_CHECKBOX_CHANGE, this, &UserInterfaceController::OnRotateCheckboxClick);

	ruiSlider* rotate_speed = (ruiSlider*)_document->GetWidget("rotate_speed");
	rotate_speed->Bind(ruiEVENT_SLIDER_CHANGE, this, &UserInterfaceController::OnRotationSpeedSliderChange);
	_rotationSpeed = rotate_speed->GetValue();

	ruiPicker* modelpicker = (ruiPicker*)_document->GetWidget("modelpicker");
	modelpicker->Bind(ruiEVENT_PICKER_CHANGE, this, &UserInterfaceController::OnModelPickerChange);

	ruiButton* reloadStyles = (ruiButton*)_document->GetWidget("reloadstyles");
	modelpicker->Bind(ruiEVENT_BUTTON_CLICK, this, &UserInterfaceController::OnModelPickerChange);
}

void UserInterfaceController::OnModelPickerChange(rEvent& event){
	ruiWidgetEvent& widgetEvent = (ruiWidgetEvent&)event;
	ruiPicker* modelpicker = (ruiPicker*)widgetEvent.Widget();

	_primitive->RenderingOptions()->SetVisibility(false);

	_primitive = (rPrimitive*)_engine->scene->GetActor(modelpicker->SelectionText());

	_primitive->RenderingOptions()->SetVisibility(true);
	ApplyRotation();

	Log::Info(modelpicker->SelectionText());
}

void OnReloadStylesClick(rEvent& event){

}

void UserInterfaceController::OnRotateCheckboxClick(rEvent& event){
	ruiWidgetEvent& widgetEvent = (ruiWidgetEvent&)event;
	ruiCheckbox* checkbox = (ruiCheckbox*)widgetEvent.Widget();

	if (checkbox->IsChecked()){
		_rotateHandle = _document->RunEveryUpdate([&](){
			_rotationValue += _rotationSpeed * _engine->time.TimeDeltaSeconds();
			ApplyRotation();
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