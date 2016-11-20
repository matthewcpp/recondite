#include "ModelViewerController.hpp"

#include "ui/ruiText.hpp"
#include "ui/ruiTextBox.hpp"
#include "ui/ruiCheckbox.hpp"
#include "ui/ruiLinearLayout.hpp"
#include "ui/ruiAbsoluteLayout.hpp"
#include "ui/ruiPicker.hpp"
#include "ui/ruiButton.hpp"
#include "ui/ruiSlider.hpp"

#include "stream/rOStringStream.hpp"
#include "stream/rIStringStream.hpp"

#include "rDemoCamera.hpp"

#include "rPawn.hpp"

ModelViewerController::ModelViewerController(ModelViewerSettings* settings, const rString& name, rEngine* engine, ruiDocument* document)
	:ruiController(name)
{
	_engine = engine;
	_document = document;
	_settings = settings;
}

void ModelViewerController::SetColorForWidgetEvent(rEvent& event, const rColor& color) {
	ruiWidget* text = _document->GetActiveWidget();
	text->Style()->SetColor("color", color);

	unsigned int index;
	if (text->Properties().GetUnsignedInt("meshIndex", index)) {
		recondite::Model* model = _engine->content->Models()->Get("model");
		model->GetTriangleMesh(index)->GetMaterial()->SetDiffuseColor(color);
	}
}

void ModelViewerController::OnMouseEnter(rEvent& event) {
	SetColorForWidgetEvent(event, rColor::Green);
}

void ModelViewerController::OnMouseLeave(rEvent& event) {
	SetColorForWidgetEvent(event, rColor::White);
}

void ModelViewerController::CameraDebug() {
	rDemoCamera* camera = (rDemoCamera*)_engine->scene->GetActor("main_camera");
	rVector3 pos = camera->Position();
	rVector3 tar = camera->Target();

	ruiText* cameraPos = (ruiText*)_document->GetWidgetById("camera-pos");
	
	rOStringStream posStr;
	posStr << "Pos: " << pos.x << ", " << pos.y << ", " << pos.z;
	cameraPos->SetText(posStr.Str());


	ruiText* cameraTar = (ruiText*)_document->GetWidgetById("camera-tar");
	rOStringStream tarStr;
	tarStr << "Tar: " << tar.x << ", " << tar.y << ", " << tar.z;
	cameraTar->SetText(tarStr.Str());
}

void ModelViewerController::OnDocumentLoaded() {
	recondite::Model* model = _engine->content->Models()->Get("model");

	ruiLayout* meshList = (ruiLayout*)_document->GetWidgetById("mesh-list");

	ruiCheckbox* displaySkeletonCheckbox = (ruiCheckbox*)_document->GetWidgetById("display-skeleton");
	displaySkeletonCheckbox->Bind(ruiEVENT_CHECKBOX_CHANGE, this, &ModelViewerController::OnShowSkeletonClick);

	ruiCheckbox* displayBoneNames = (ruiCheckbox*)_document->GetWidgetById("display-bone-names");
	displayBoneNames->Bind(ruiEVENT_CHECKBOX_CHANGE, this, &ModelViewerController::OnShowBoneNamesClick);

	
	for (size_t i = 0; i < model->GetTriangleMeshCount(); i++) {
		rString meshName = model->GetTriangleMesh(i)->GetName();

		rOStringStream id;
		id << "Mesh " << i;

		if (meshName.empty()) {
			meshName = id.Str();
		}

		ruiText* text = new ruiText(meshName, id.Str(), _document, _engine);
		text->Properties().SetUnsignedInt("meshIndex", i);
		text->Bind(ruiEVT_MOUSE_ENTER, this, &ModelViewerController::OnMouseEnter);
		text->Bind(ruiEVT_MOUSE_LEAVE, this, &ModelViewerController::OnMouseLeave);

		meshList->AddItem(text);
	}

	ruiPicker* animationPicker = (ruiPicker*)_document->GetWidgetById("animation-picker");

	recondite::Skeleton* skeleton = model->GetSkeleton();
	if (skeleton) {
		for (size_t i = 0; i < skeleton->GetAnimationCount(); i++) {
			recondite::Animation* animation = skeleton->GetAnimation(i);

			animationPicker->AddOption(animation->Name());
		}
	}


	if (_settings->animatedModel && skeleton->GetAnimationCount() > 0) {
		rPawn* pawn = (rPawn*)_engine->scene->GetActor("model");
		pawn->AnimationController()->SetAnimation(animationPicker->Options()[0]);
	}

	animationPicker->Bind(ruiEVENT_PICKER_CHANGE, this, &ModelViewerController::OnAnimationPickerChange);

	ruiButton* playButton = (ruiButton*)_document->GetWidgetById("animation-play");
	playButton->Bind(ruiEVENT_BUTTON_CLICK, this, &ModelViewerController::OnAnimationPlayButtonClick);

	ruiButton* pauseButton = (ruiButton*)_document->GetWidgetById("animation-pause");
	pauseButton->Bind(ruiEVENT_BUTTON_CLICK, this, &ModelViewerController::OnAnimationPauseButtonClick);

	ruiButton* stopButton = (ruiButton*)_document->GetWidgetById("animation-stop");
	stopButton->Bind(ruiEVENT_BUTTON_CLICK, this, &ModelViewerController::OnAnimationStopButtonClick);

	ruiCheckbox* loopCheckBox = (ruiCheckbox*)_document->GetWidgetById("animation-loop");
	loopCheckBox->Bind(ruiEVENT_CHECKBOX_CHANGE, this, &ModelViewerController::OnAnimationLoopCheckboxClick);

	ruiSlider* animationProgress = (ruiSlider*)_document->GetWidgetById("animation-progress");
	animationProgress->Bind(ruiEVENT_SLIDER_DRAG_MOVE, this, &ModelViewerController::OnAnimationProgressDrag);

	ruiTextBox* animationSpeed = (ruiTextBox*)_document->GetWidgetById("animation-speed");
	animationSpeed->Bind(ruiEVT_KEY_UP, this, &ModelViewerController::OnAnimationSpeedKey);

	_document->RunEveryUpdate([&]() {
		OnUpdate();
	});


}

void ModelViewerController::OnAnimationProgressDrag(rEvent& event) {
	rPawn* pawn = (rPawn*)_engine->scene->GetActor("model");
	auto animationController = pawn->AnimationController();

	ruiSlider* slider = (ruiSlider*)_document->GetWidgetById("animation-progress");

	animationController->SetAnimationTime(animationController->GetAnimation()->Duration() * slider->GetValue());
}

void ModelViewerController::OnUpdate() {
	CameraDebug();

	rPawn* pawn = (rPawn*)_engine->scene->GetActor("model");
	auto animationController = pawn->AnimationController();

	if (animationController->IsPlaying()) {
		ruiSlider* slider = (ruiSlider*)_document->GetWidgetById("animation-progress");
		slider->SetValue(animationController->GetAnimationTime() / animationController->GetAnimation()->Duration());
	}
}

void ModelViewerController::OnShowSkeletonClick(rEvent& event) {
	ruiWidgetEvent& evt = (ruiWidgetEvent&)event;
	ruiCheckbox* checkbox = (ruiCheckbox*)evt.Widget();

	_settings->renderSkeleton = checkbox->IsChecked();
}

void ModelViewerController::OnShowBoneNamesClick(rEvent& event) {
	ruiWidgetEvent& evt = (ruiWidgetEvent&)event;
	ruiCheckbox* checkbox = (ruiCheckbox*)evt.Widget();

	_settings->renderBoneNames = checkbox->IsChecked();
}

void ModelViewerController::OnAnimationPickerChange(rEvent& event) {
	rPawn* pawn = (rPawn*)_engine->scene->GetActor("model");
	ruiPicker* animationPicker = (ruiPicker*)_document->GetWidgetById("animation-picker");
	recondite::AnimationController* animationController = pawn->AnimationController();

	bool wasPlaying = animationController->IsPlaying();
	animationController->SetAnimation(animationPicker->SelectionText());

	if (wasPlaying)
		animationController->Play();
}

void ModelViewerController::OnAnimationPlayButtonClick(rEvent& event) {
	rPawn* pawn = (rPawn*)_engine->scene->GetActor("model");
	pawn->AnimationController()->Play();
}

void ModelViewerController::OnAnimationPauseButtonClick(rEvent& event) {
	rPawn* pawn = (rPawn*)_engine->scene->GetActor("model");
	pawn->AnimationController()->Pause();
}

void ModelViewerController::OnAnimationStopButtonClick(rEvent& event) {
	rPawn* pawn = (rPawn*)_engine->scene->GetActor("model");
	pawn->AnimationController()->Stop();
}

void ModelViewerController::OnAnimationLoopCheckboxClick(rEvent& event) {
	ruiCheckbox* animationLoop = (ruiCheckbox*)_document->GetWidgetById("animation-loop");
	rPawn* model = (rPawn*)_engine->scene->GetActor("model");
	model->AnimationController()->SetLoop(animationLoop->IsChecked());
}

void ModelViewerController::OnAnimationSpeedKey(rEvent& event) {
	ruiKeyEvent& keyEvent = (ruiKeyEvent&)event;
	char key = char(keyEvent.Key());

	if (key == rKEY_ENTER) {
		ruiTextBox* animationSpeed = (ruiTextBox*)_document->GetWidgetById("animation-speed");
		rIStringStream str(animationSpeed->GetText());

		float newSpeed = 0;
		str >> newSpeed;

		rPawn* pawn = (rPawn*)_engine->scene->GetActor("model");
		pawn->AnimationController()->SetSpeed(newSpeed);
	}
	

	
}