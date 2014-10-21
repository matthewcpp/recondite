#include "rApplication.hpp"

rApplication::rApplication(){
	m_isRunning = false;
	m_frameCount = 0;
	m_targetFPS = 30;
}

void rApplication::Update(){
	m_module->BeforeUpdateScene(m_engine);
		m_scene->Update(m_engine);
	m_module->AfterUpdateScene(m_engine);

	m_overlayManager->Update(m_engine);
}

bool rApplication::LoadModule(const char* path){
	m_module = m_moduleLoader.LoadModule(path);

	return m_module != NULL;
}

void rApplication::Draw(){
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
		m_scene->Draw(m_engine);
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
		view.overlay->Draw(m_engine);
		m_module->AfterRenderOverlay(view, m_engine);
	}

	m_graphicsDevice->SwapBuffers();

	m_frameCount++;
}

rApplication::~rApplication(){
}

bool rApplication::IsRunning() const{
	return m_isRunning;
}

void rApplication::Tick(){
	unsigned long time = GetTimeMiliseconds();

	unsigned long delta = time - m_engine.time.LastUpdateTime();
	unsigned int ms = 1000 / m_targetFPS;

	if (delta >= ms){
		m_engine.time.Update(time);
		Update();
		Draw();
	}
}

size_t rApplication::TargetFPS() const{
	return m_targetFPS;
}

void rApplication::SetTargetFPS(unsigned int targetFPS){
	m_targetFPS = targetFPS;
}

void rApplication::InitEngine(rGraphicsDevice* graphics, rContentManager* content, rInputManager* input){
	m_graphicsDevice = graphics; 

	m_overlayManager = new ruiOverlayManager(&m_engine);
	input->SetUI(m_overlayManager);

	m_engine.application = this;

	m_engine.ui = m_overlayManager;
	m_engine.content = content;
	m_engine.input = input;
	m_engine.renderer = new rRenderer(graphics, content);
	m_engine.time.Start(GetTimeMiliseconds());

	m_scene = new rScene();
	m_engine.scene = m_scene;

	m_isRunning = true;

	m_graphicsDevice->Init();
	m_engine.content->InitDefaultAssets();
	m_engine.renderer->CreateRequiredMaterials();
}

void rApplication::InitModule(){
	m_module->Init(m_engine);
	m_module->InitUI(*m_overlayManager, m_engine);
	m_module->LoadScene("Default", m_engine);
}

void rApplication::SetDisplaySize(int width, int height){
	m_displaySize.Set(width, height);
}

rSize rApplication::DisplaySize() const{
	return m_displaySize;
}

rViewport* rApplication::CreateViewport(const rString& name){
	if (m_viewports.count(name)){
		return NULL;
	}
	else {
		rViewport* viewport = new rViewport(name);
		m_viewports[name] = viewport;
		return viewport;
	}
}

rViewport* rApplication::GetViewport(const rString& name) const{
	rViewportMap::const_iterator it = m_viewports.find(name);

	if (it != m_viewports.end()){
		return it->second;
	}
	else{
		return NULL;
	}
}

void rApplication::DeleteViewport(const rString& name){
	rViewportMap::iterator it = m_viewports.find(name);

	if (it != m_viewports.end()){
		delete it->second;
		m_viewports.erase(it);
	}
}

size_t rApplication::NumViewports() const{
	return m_viewports.size();
}

size_t rApplication::FrameCount() const{
	return m_frameCount;
}

bool rApplication::Init(){
	return true;
}

void rApplication::Uninit(){
	m_module->Uninit(m_engine);
	rLog::Shutdown();
}