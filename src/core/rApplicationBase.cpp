#include "rApplicationBase.hpp"

rApplicationBase::rApplicationBase(){
	m_module = NULL;
	m_frameCount = 0;
	m_targetFPS = 30;

	m_displaySize.Set(1024, 768);
}

void rApplicationBase::Update(){
	m_module->BeforeUpdateScene();
		m_scene->Update();
	m_module->AfterUpdateScene();

	m_overlayManager->Update();

	m_engine.input->PostUpdate();
}

void rApplicationBase::Draw(){
	m_graphicsDevice->Clear();

	rViewportMap::iterator end = m_viewports.end();
	
	//render the scene in each viewport
	m_graphicsDevice->EnableDepthTesting(true);
	for (rViewportMap::iterator it = m_viewports.begin(); it != end; ++it){
		rViewInfo viewInfo;
		viewInfo.viewport = it->second;
		viewInfo.overlay = m_overlayManager->GetOverlay(viewInfo.viewport);

		m_engine.renderer->BeginRenderView(*viewInfo.viewport);
		m_module->BeforeRenderScene(&viewInfo);
		m_scene->Draw();
		m_module->AfterRenderScene(&viewInfo);
		m_engine.renderer->EndRenderView();
	}

	//render the overlay for each viewport
	m_graphicsDevice->EnableDepthTesting(false);
	for (rViewportMap::iterator it = m_viewports.begin(); it != end; ++it){
		rViewInfo view;
		view.viewport = it->second;
		view.overlay = m_overlayManager->GetOverlay(view.viewport);

		m_overlayManager->Draw(view.viewport);
	}

	m_graphicsDevice->SwapBuffers();

	m_frameCount++;
}

rApplicationBase::~rApplicationBase(){
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
	m_module = CreateModule(&m_engine);
	m_module->Init();
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

void rApplicationBase::InitEngine(rGraphicsDevice* graphics, rContentManager* content, rInputManager* input, rFileSystem* fileSystem){
	rComponent::InitEngine(graphics, content, input, fileSystem);
}


void rApplicationBase::Uninit(){
	m_module->Uninit();

	rComponent::Uninit();
}