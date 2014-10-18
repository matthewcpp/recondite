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
#include "ui/ruiAbsoluteLayout.hpp"

void BasicSceneModule::InitUI(ruiOverlayManager& manager, rEngine& engine){
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
	p->AddOption("Test 2");
	p->AddOption("Test 3");
	absoluteLayout->AddItem(p);
	overlay->AddWidget(p);

}

void BasicSceneModule::Uninit(rEngine& engine){
}

void BasicSceneModule::LoadScene(const rString& sceneName, rEngine& engine){
}

void BasicSceneModule::DeleteActor(rActor3* actor){
}