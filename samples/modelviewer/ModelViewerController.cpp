#include "ModelViewerController.hpp"

#include "ui/ruiText.hpp"
#include "ui/ruiCheckbox.hpp"
#include "ui/ruiLinearLayout.hpp"
#include "ui/ruiAbsoluteLayout.hpp"
#include "ui/ruiPicker.hpp"

#include "stream/rOStringStream.hpp"

#include "rDemoCamera.hpp"

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
		for (size_t i = 0; i < skeleton->NumAnimations(); i++) {
			recondite::Animation* animation = skeleton->GetAnimation(i);

			animationPicker->AddOption(animation->Name());
		}
	}

	_document->RunEveryUpdate([&]() {
		CameraDebug();
	});
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