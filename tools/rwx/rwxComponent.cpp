#include "rwxComponent.hpp"
#include "wx/filename.h"

rwxComponent::rwxComponent(){
	m_rwxGraphicsDevice = nullptr;
	m_rglContentManager = nullptr;
	m_rInputManager = nullptr;
	m_resourceManager = nullptr;
}

bool rwxComponent::Init(){
	rFileSystem* fileSystem = new rFileSystem();
	m_rwxGraphicsDevice = new rwxOpenGLGraphicsDevice();
	m_rglContentManager = new rOpenGLContentManager(m_rwxGraphicsDevice, fileSystem, m_resourceManager);
	m_rInputManager = new rInputManager();

	

	InitEngine(m_rwxGraphicsDevice, m_rglContentManager, m_rInputManager, fileSystem, (recondite::ResourceManager*)m_resourceManager);

	rComponent::Init();

	return true;
}

void rwxComponent::InitGraphics(wxGLCanvas* canvas) {
	m_rwxGraphicsDevice->Init(canvas);
	LoadDefaultResources();
}

void rwxComponent::RenderScene(rViewport* viewport){
	m_graphicsDevice->Clear();

	m_engine->viewports->SetActiveViewport(viewport);
	rRect window = viewport->GetScreenRect();
	m_graphicsDevice->SetViewport(window.x, window.y, window.width, window.height);

	rMatrix4 projection, view;
	viewport->GetProjectionMatrix(projection);
	viewport->GetViewMatrix(view);

	m_engine->renderer->SetModelRenderMode(viewport->RenderMode());

	m_engine->renderer->Begin(projection, view);
	BeforeSceneRendered(viewport);
	((rScene*)m_engine->scene)->Draw();
	AfterSceneRendered(viewport);
	m_engine->renderer->End();
	m_engine->viewports->SetActiveViewport(nullptr);
}

rSize rwxComponent::DisplaySize() const{
	return rSize(0, 0);
}

unsigned long rwxComponent::GetTimeMiliseconds() const{
	return 0;
}

rwxOpenGLGraphicsDevice* rwxComponent::GraphicsDevice(){
	return m_rwxGraphicsDevice;
}

rOpenGLContentManager* rwxComponent::ContentManager(){
	return m_rglContentManager;
}

rInputManager* rwxComponent::InputManager(){
	return m_rInputManager;
}

wxGLContext* rwxComponent::GetContext(){
	return m_rwxGraphicsDevice->GetContext();
}

rString rwxComponent::GetBasePath(){
	wxFileName exePath(wxStandardPaths::Get().GetExecutablePath());

	return exePath.GetPath(wxPATH_GET_SEPARATOR).c_str().AsChar();
}

void rwxComponent::SetResourceManager(recondite::iResourceManager* resourceManager) {
	m_resourceManager = resourceManager;
}