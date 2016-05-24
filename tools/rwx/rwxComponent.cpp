#include "rwxComponent.hpp"
#include "wx/filename.h"

rwxComponent::rwxComponent(){
	m_rwxGraphicsDevice = NULL;
	m_rglContentManager = NULL;
	m_rInputManager = NULL;
}

bool rwxComponent::Init(wxGLCanvas* canvas){
	rFileSystem* fileSystem = new rFileSystem();
	m_rwxGraphicsDevice = new rwxOpenGLGraphicsDevice();
	m_rglContentManager = new rOpenGLContentManager(m_rwxGraphicsDevice, fileSystem);
	m_rInputManager = new rInputManager();

	m_rwxGraphicsDevice->Init(canvas);

	InitEngine(m_rwxGraphicsDevice, m_rglContentManager, m_rInputManager, fileSystem);

	rComponent::Init();

	rEvent event;
	Trigger(rEVT_COMPONENT_INITIALIZED, event);

	return true;
}

void rwxComponent::RenderScene(rViewport* viewport){
	m_graphicsDevice->Clear();

	rRect window = viewport->GetScreenRect();
	m_graphicsDevice->SetViewport(window.x, window.y, window.width, window.height);

	rMatrix4 projection, view;
	viewport->GetProjectionMatrix(projection);
	viewport->GetViewMatrix(view);

	m_engine.renderer->Begin(projection, view);
	m_scene->Draw();
	m_engine.renderer->End();
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

	return exePath.GetPath().c_str().AsChar();
}