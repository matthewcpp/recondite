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

void BasicSceneModule::Init(rEngine& engine){
	rSize displaySize = engine.application->DisplaySize();

	rViewport* viewport = engine.application->CreateViewport("main");
	viewport->SetClipping(0.5,1000);
	viewport->SetSize(displaySize);
	viewport->SetViewportType(rVIEWPORT_PERSP);

	viewport->SetCamera(new rViewCamera("camera", rVector3(0, 0, 3)));

	rLogContentListener listener;

	engine.content->AddListener(&listener);
	engine.content->LoadAssetManifestFromPath("content/basicscene/manifest.xml");
	engine.content->RemoveListener(&listener);

	engine.scene->AddActor(new rPrimitiveBox("box1", rAlignedBox3(0,0,0,1,1,1), rColor::Green));
	engine.scene->AddActor(new rPrimitiveBox("box2", rAlignedBox3(-2,0,0,-1,1,1), rColor::Blue));
}

#include "ui/ruiPicker.hpp"
#include "ui/ruiAbsoluteLayout.hpp"

void BasicSceneModule::InitUI(ruiOverlayManager& manager, rEngine& engine){
	manager.CreateOverlay("content/basicscene/ui/basicscene.rtml", engine.application->GetViewport("main"));

	/*
	rAssetStream cssFile = engine.content->LoadTextFromPath("content/basicscene/ui/basicscene.rss");
	
	if (cssFile)
		engine.ui->Styles()->ParseStylesheet(*cssFile);

	ruiOverlay* overlay = manager.CreateOverlay(engine.application->GetViewport("main"));
	ruiAbsoluteLayout* absoluteLayout = new ruiAbsoluteLayout();
	overlay->SetLayout(absoluteLayout);
	m_textCameraPos = new ruiText("camera-text", &engine);
	absoluteLayout->AddItem(m_textCameraPos);
	overlay->AddWidget(m_textCameraPos);

	ruiText* txt = new ruiText("The time has come for all good men to come to the aid of their country\nthe greatest generation\n1945","greatest_text", &engine);
	absoluteLayout->AddItem(txt);
	overlay->AddWidget(txt);
	
	ruiPicker* p = new ruiPicker("picker1", &engine);

	p->AddOption("Test 1");
	p->AddOption("THis option is pretty long...");
	p->AddOption("Test 3");
	absoluteLayout->AddItem(p);
	overlay->AddWidget(p);
	*/
}

void BasicSceneModule::Uninit(rEngine& engine){
}

void BasicSceneModule::LoadScene(const rString& sceneName, rEngine& engine){
}

void BasicSceneModule::DeleteActor(rActor3* actor){
}