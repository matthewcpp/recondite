#include "BasicSceneModule.hpp"
#include "rLog.hpp"

void BasicSceneModule::BeforeUpdateScene(rEngine& engine){
	rViewport* viewport = engine.application->GetViewport("main");
	rCamera* camera = (rCamera*)viewport->Camera();

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

	if (keyboard->GetKeyState('e') == rKEY_DOWN){
		rVector3 rot = camera->Rotation();
		rot.y -= 90 * engine.time.TimeDeltaSeconds();
		camera->SetRotation(rot);
	}
	else if (keyboard->GetKeyState('q') == rKEY_DOWN){
		rVector3 rot = camera->Rotation();
		rot.y += 90 * engine.time.TimeDeltaSeconds();
		camera->SetRotation(rot);
	}

	const rMouseState* mouseState = engine.input->GetMouseState();
	if (mouseState->Button(rMOUSE_BUTTON_LEFT).Pressed()){
		m_drawRay = true;
		rPoint mousePos = mouseState->Position();
		/*
		rLog::Info("raycast select: %d, %d", mousePos.x, mousePos.y);
		viewport->GetSelectionRay(mousePos, m_ray);
		*/

		rLog::Info("viewport select: %d, %d", mousePos.x, mousePos.y);
		m_engine->scene->ViewportPick("main", mousePos.x, mousePos.y);

		rActor3* actor = engine.scene->RayPick(m_ray);

		if (actor){
			rLog::Info("Selected Actor: %s", actor->Id().c_str());
		}
	}
}

void BasicSceneModule::AfterUpdateScene(rEngine& engine){
}

void BasicSceneModule::BeforeRenderScene(rViewInfo& view, rEngine& engine){	
}

void BasicSceneModule::AfterRenderScene(rViewInfo& view, rEngine& engine){
	if (m_drawRay){
		rImmediateBuffer buffer(rGEOMETRY_LINES,3,false);
		buffer.PushVertex(m_ray.origin);
		buffer.PushVertex(m_ray.direction * 50.0f);

		buffer.PushIndex(0,1);

		rMatrix4 ident;
		engine.renderer->Render3dBuffer(buffer, ident, rColor(255,176,250,255));
	}

			rActor3* box = m_engine->scene->GetActor("box01");
		riBoundingVolume* boundingVolume = box->BoundingVolume();
		engine.renderer->RenderWireBox(boundingVolume->FitBox(), rColor::Green);
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

	engine.application->RegisterActorLoader("PrimitiveBox", new rPrimitiveBoxReader());
	engine.application->RegisterActorLoader("PrimitiveCone", new rPrimitiveConeReader());
	engine.application->RegisterActorLoader("PrimitiveCylinder", new rPrimitiveCylinderReader());
	engine.application->RegisterActorLoader("PrimitiveSphere", new rPrimitiveSphereReader());
	engine.application->RegisterActorLoader("PrimitiveGrid", new rPrimitiveGridReader());

	engine.application->LoadScene("content/basicscene/levels/world.rlvl");
	
	m_drawRay = false;
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