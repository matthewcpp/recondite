#include "rApplication.hpp"

rApplication::rApplication(){
	m_isRunning = false;
	m_frameCount = 0;
}

void rApplication::Update(){
	m_scene->Update(m_engine);
	m_overlayManager->Update(m_engine);
	
	m_module->Update(m_engine);
}

bool rApplication::LoadModule(const char* path){
	m_module = m_moduleLoader.LoadModule(path);

	return m_module != NULL;
}

void rApplication::Draw(){
	m_graphicsDevice->Clear();

	//application level rendering goes here...
	m_graphicsDevice->EnableDepthTesting(true);

	m_module->Draw(m_engine);
	m_scene->Draw(m_engine);

	m_graphicsDevice->EnableDepthTesting(false);
	m_overlayManager->Draw(m_engine);

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

unsigned int rApplication::GetTargetFPS() const{
	return m_targetFPS;
}

void rApplication::SetTargetFPS(unsigned int targetFPS){
	m_targetFPS = targetFPS;
}

void rApplication::InitEngine(rGraphicsDevice* graphics, rContentManager* content, rInputManager* input){
	m_graphicsDevice = graphics; 

	m_overlayManager = new ruiOverlayManager();
	input->SetUI(m_overlayManager);

	m_engine.application = this;

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