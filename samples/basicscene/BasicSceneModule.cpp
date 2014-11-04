#include "BasicSceneModule.hpp"

void BasicSceneModule::BeforeUpdateScene(rEngine& engine){
	rCamera* camera = (rCamera*)engine.application->GetViewport("main")->Camera();

	float distance = 10 * engine.time.TimeDeltaSeconds();

	const rKeyboardState* keyboard = engine.input->Keyboard();

	if (keyboard->GetKeyState('w') == rKEY_DOWN){
		camera->MoveForward(distance);
	}
	else if (keyboard->GetKeyState('s') == rKEY_DOWN){
		camera->MoveBackward(distance);
	}

	if (keyboard->GetKeyState('a') == rKEY_DOWN){
		camera->MoveLeft(distance);
	}
	else if (keyboard->GetKeyState('d') == rKEY_DOWN){
		camera->MoveRight(distance);
	}

	if (keyboard->GetKeyState('r') == rKEY_DOWN){
		camera->MoveUp(distance);
	}
	else if (keyboard->GetKeyState('f') == rKEY_DOWN){
		camera->MoveDown(distance);
	}
}

void BasicSceneModule::AfterUpdateScene(rEngine& engine){
}

void BasicSceneModule::BeforeRenderScene(rViewInfo& view, rEngine& engine){	
}

void BasicSceneModule::AfterRenderScene(rViewInfo& view, rEngine& engine){

}

void BasicSceneModule::BeforeRenderOverlay(rViewInfo& view, rEngine& engine){
	riCamera* camera = view.viewport->Camera();
	rVector3 pos = camera->Position();

	rOStringStream str;
	str << "camera: " << pos.x << ", " << pos.y << ", " << pos.z;


	ruiText* cameraText = (ruiText*)view.overlay->GetWidget("camera-text");
	if (cameraText) 
		cameraText->SetText(str.Str());
}

void BasicSceneModule::AfterRenderOverlay(rViewInfo& view, rEngine& engine){
}

#include "data/rLogContentListener.hpp"
#include "primitive/rPrimitiveSerialization.hpp"

void BasicSceneModule::Init(rEngine& engine){
	rSize displaySize = engine.application->DisplaySize();

	rViewport* viewport = engine.application->CreateViewport("main");
	viewport->SetClipping(0.5,1000);
	viewport->SetSize(displaySize);
	viewport->SetViewportType(rVIEWPORT_PERSP);

	rViewCamera* camera = new rViewCamera("camera", &engine);
	camera->SetPosition(0, 1.0f, 10.0f);

	viewport->SetCamera(camera);

	rLogContentListener listener;

	engine.content->AddListener(&listener);
	engine.content->LoadAssetManifestFromPath("content/basicscene/manifest.xml");
	engine.content->RemoveListener(&listener);

	engine.scene->RegisterActorLoader("PrimitiveBox", new rPrimitiveBoxReader());
	engine.application->LoadScene("content/basicscene/levels/world.rlvl");
	
}

#include "ui/ruiPicker.hpp"
#include "ui/ruiAbsoluteLayout.hpp"

void BasicSceneModule::ReloadLevel(){
	m_engine->application->LoadScene("content/basicscene/levels/world.rlvl");
}

void BasicSceneModule::ReloadButtonClick(rEvent& event){
	ReloadLevel();
}

void BasicSceneModule::InitUI(ruiOverlayManager& manager, rEngine& engine){
	m_overlayManager = &manager;
	m_engine = &engine;

	ruiOverlay* overlay = m_overlayManager->CreateOverlay("content/basicscene/ui/basicscene.rtml", m_engine->application->GetViewport("main"));

	ruiWidget* reloadButton = overlay->GetWidget("reload-button");
	reloadButton->Bind(ruiEVENT_BUTTON_CLICK, this, &BasicSceneModule::ReloadButtonClick);
}

void BasicSceneModule::Uninit(rEngine& engine){
}

void BasicSceneModule::LoadScene(const rString& sceneName, rEngine& engine){
}

void BasicSceneModule::DeleteActor(rActor3* actor){
}