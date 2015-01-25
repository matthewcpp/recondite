#include "rApplicationBase.hpp"

rApplicationBase::rApplicationBase(){
	m_module = NULL;
	m_isRunning = false;
	m_frameCount = 0;
	m_targetFPS = 30;
}

void rApplicationBase::Update(){
	m_module->BeforeUpdateScene(m_engine);
		m_scene->Update();
	m_module->AfterUpdateScene(m_engine);

	m_overlayManager->Update(m_engine);

	m_engine.input->PostUpdate();
}

void rApplicationBase::Draw(){
	m_graphicsDevice->Clear();

	rViewportMap::iterator end = m_viewports.end();
	
	//render the scene in each viewport
	m_graphicsDevice->EnableDepthTesting(true);
	for (rViewportMap::iterator it = m_viewports.begin(); it != end; ++it){
		rViewInfo view;
		view.viewport = it->second;
		view.overlay = m_overlayManager->GetOverlay(view.viewport);

		m_engine.renderer->BeginRenderView(*view.viewport);
		m_module->BeforeRenderScene(view, m_engine);
		m_scene->Draw();
		m_module->AfterRenderScene(view, m_engine);
		m_engine.renderer->EndRenderView();
	}

	//render the overlay for each viewport
	m_graphicsDevice->EnableDepthTesting(false);
	for (rViewportMap::iterator it = m_viewports.begin(); it != end; ++it){
		rViewInfo view;
		view.viewport = it->second;
		view.overlay = m_overlayManager->GetOverlay(view.viewport);

		m_module->BeforeRenderOverlay(view, m_engine);
		m_overlayManager->Draw(view.viewport);
		m_module->AfterRenderOverlay(view, m_engine);
	}

	m_overlayManager->DrawFinal();

	m_graphicsDevice->SwapBuffers();

	m_frameCount++;
}

rApplicationBase::~rApplicationBase(){
}

bool rApplicationBase::IsRunning() const{
	return m_isRunning;
}

void rApplicationBase::Tick(){
	unsigned long time = GetTimeMiliseconds();

	unsigned long delta = time - m_engine.time.LastUpdateTime();
	unsigned int ms = 1000 / m_targetFPS;

	if (delta >= ms){
		m_engine.time.Update(time);
		Update();
		Draw();
	}
}

size_t rApplicationBase::TargetFPS() const{
	return m_targetFPS;
}

void rApplicationBase::SetTargetFPS(unsigned int targetFPS){
	m_targetFPS = targetFPS;
}

void rApplicationBase::InitModule(){
	m_module = CreateModule();
	
	m_module->Init(m_engine);
	m_module->InitUI(*m_overlayManager, m_engine);
	m_module->LoadScene("Default", m_engine);
}

void rApplicationBase::SetDisplaySize(int width, int height){
	m_displaySize.Set(width, height);
}

rSize rApplicationBase::DisplaySize() const{
	return m_displaySize;
}

size_t rApplicationBase::FrameCount() const{
	return m_frameCount;
}

void rApplicationBase::InitEngine(rGraphicsDevice* graphics, rContentManager* content, rInputManager* input){
	rComponent::InitEngine(graphics, content, input);
	m_isRunning = true;
}


void rApplicationBase::Uninit(){
	m_module->Uninit(m_engine);

	rComponent::Uninit();
}