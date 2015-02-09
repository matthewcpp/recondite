#include "rwxComponent.hpp"

rwxComponent::rwxComponent(){
	m_rwxGraphicsDevice = NULL;
	m_rglContentManager = NULL;
	m_rInputManager = NULL;
}

bool rwxComponent::Init(wxGLCanvas* canvas){
	m_rwxGraphicsDevice = new rwxOpenGLGraphicsDevice();
	m_rglContentManager = new rOpenGLContentManager(m_rwxGraphicsDevice);
	m_rInputManager = new rInputManager();

	m_rwxGraphicsDevice->Init(canvas);

	InitEngine(m_rwxGraphicsDevice, m_rglContentManager, m_rInputManager);

	rComponent::Init();

	return true;
}

void rwxComponent::RenderScene(rViewport* viewport){
	m_graphicsDevice->Clear();

	m_engine.renderer->BeginRenderView(*viewport);
	m_scene->Draw();
	m_engine.renderer->EndRenderView();
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