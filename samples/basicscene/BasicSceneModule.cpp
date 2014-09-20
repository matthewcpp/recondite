#include "BasicSceneModule.hpp"

void BasicSceneModule::BeforeUpdateScene(rEngine& engine){
	rOStringStream str;
	rVector3 pos = m_camera->Position();

	str << "camera: " << pos.x << ", " << pos.y << ", " << pos.z;


	m_textCameraPos->SetText(str.Str());

	float distance = 10 * engine.time.TimeDeltaSeconds();

	const rKeyboardState* keyboard = engine.input->Keyboard();

	if (keyboard->GetKeyState('w') == rKEY_DOWN){
		m_camera->MoveForward(distance);
	}
	else if (keyboard->GetKeyState('s') == rKEY_DOWN){
		m_camera->MoveBackward(distance);
	}

	if (keyboard->GetKeyState('a') == rKEY_DOWN){
		m_camera->MoveLeft(distance);
	}
	else if (keyboard->GetKeyState('d') == rKEY_DOWN){
		m_camera->MoveRight(distance);
	}

	if (keyboard->GetKeyState('r') == rKEY_DOWN){
		m_camera->MoveUp(distance);
	}
	else if (keyboard->GetKeyState('f') == rKEY_DOWN){
		m_camera->MoveDown(distance);
	}
}

void BasicSceneModule::AfterUpdateScene(rEngine& engine){
}

void BasicSceneModule::BeforeRenderScene(rViewInfo& view, rEngine& engine){	
}

void BasicSceneModule::AfterRenderScene(rViewInfo& view, rEngine& engine){
	rOStringStream str;
	ruiText* renderInfo = (ruiText*)view.overlay->GetWidget("2");
	size_t actorCount = engine.scene->NumActors();
	size_t renderCount = engine.renderer->ObjectsRendered();

	str << "Rendered: " << renderCount <<'/' << actorCount << " actors";
	renderInfo->SetText(str.Str());
}

void BasicSceneModule::BeforeRenderOverlay(rViewInfo& view, rEngine& engine){
}

void BasicSceneModule::AfterRenderOverlay(rViewInfo& view, rEngine& engine){
}

void BasicSceneModule::Init(rEngine& engine){
	rSize displaySize = engine.application->DisplaySize();

	rViewport* viewport = engine.application->CreateViewport("main");
	viewport->SetClipping(0.5,1000);
	viewport->SetSize(displaySize);
	viewport->SetViewportType(rVIEWPORT_PERSP);

	m_camera = new rViewCamera("camera", rVector3(0, 0, 3));
	viewport->SetCamera(m_camera);

	engine.content->LoadFontFromPath("content/fonts/Consolas.rfnt", "consolas");

	engine.scene->AddActor(new rPrimitiveBox("box1", rAlignedBox3(0,0,0,1,1,1), rColor::Green));
	engine.scene->AddActor(new rPrimitiveBox("box2", rAlignedBox3(-2,0,0,-1,1,1), rColor::Blue));
}

#include "ui/ruiPicker.hpp"

void BasicSceneModule::InitUI(ruiOverlayManager& manager, rEngine& engine){
	ruiOverlay* overlay = manager.CreateOverlay(engine.application->GetViewport("main"));
	m_textCameraPos = new ruiText("1", &engine, rPoint(10,10));
	overlay->AddWidget(m_textCameraPos);

	overlay->AddWidget(new ruiText("The time has come for all good men to come to the aid of their country\nthe greatest generation\n1945","2", &engine, rPoint(10,50)));
	ruiPicker* p = new ruiPicker("checkbox1", &engine, rPoint(10, 200));
	p->AddOption("Test 1");
	p->AddOption("Test 2");
	p->AddOption("Test 3");
	overlay->AddWidget(p);

}

void BasicSceneModule::Uninit(rEngine& engine){
}

void BasicSceneModule::LoadScene(const rString& sceneName, rEngine& engine){
}

void BasicSceneModule::DeleteActor(rActor3* actor){
}