#include "rApplication.hpp"

rApplication::rApplication(rModule* module){
	m_isRunning = false;
	m_frameCount = 0;

	m_module = module;
}

void rApplication::Update(){
	m_layoutManager->Update(m_engine);

	m_module->Update(m_engine);
}

void rApplication::Draw(){
	m_graphicsDevice->Clear();

	//application level rendering goes here...
	m_graphicsDevice->EnableDepthTesting(true);

	m_module->Draw(m_engine);

	m_graphicsDevice->EnableDepthTesting(false);
	m_layoutManager->Draw(m_engine);

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

	m_layoutManager = new ruiLayoutManager();
	input->SetUI(m_layoutManager);

	m_engine.application = this;

	m_engine.content = content;
	m_engine.input = input;
	m_engine.renderer = new rRenderer(graphics, content);
	m_engine.time.Start(GetTimeMiliseconds());

	m_isRunning = true;

	m_graphicsDevice->Init();
	m_engine.content->InitDefaultAssets();
	m_engine.renderer->CreateRequiredMaterials();

	m_module->Init(m_engine);
	m_module->InitUI(*m_layoutManager, m_engine);
}

void rApplication::SetDisplaySize(int width, int height){
	m_displaySize.Set(width, height);
}

rSize rApplication::DisplaySize() const{
	return m_displaySize;
}