#include "rApplicationBase.hpp"

rApplicationBase::rApplicationBase(){
	m_module = NULL;
	m_frameCount = 0;
	m_targetFPS = 30;

	m_displaySize.Set(1024, 768);
}

void rApplicationBase::SetArgs(int argc, char** argv) {
	for (int i = 1; i < argc; i++) {
		args.emplace_back(argv[i]);
	}
}

void rApplicationBase::Update(){
	m_module->BeforeUpdateScene();
		m_scene->Update();
	m_module->AfterUpdateScene();

	m_uiManager->Update();

	m_engine.input->PostUpdate();
}

void rApplicationBase::Draw(){
	m_graphicsDevice->Clear();

	rViewportMap::iterator end = m_viewports.end();
	
	//render the scene in each viewport
	m_graphicsDevice->EnableDepthTesting(true);
	for (rViewportMap::iterator it = m_viewports.begin(); it != end; ++it){
		rViewport* viewport = it->second;

		rRect window = viewport->GetScreenRect();
		m_graphicsDevice->SetViewport(window.x, window.y, window.width, window.height);

		rMatrix4 projection, view;
		viewport->GetProjectionMatrix(projection);
		viewport->GetViewMatrix(view);

		m_engine.renderer->Begin(projection, view);
		m_module->BeforeRenderScene(viewport);
		m_scene->Draw();
		m_module->AfterRenderScene(viewport);
		m_engine.renderer->End();
	}

	//render the document for each viewport
	for (rViewportMap::iterator it = m_viewports.begin(); it != end; ++it){
		rViewport* viewport = it->second;

		rMatrix4 matrixOrtho2D, identity;
		rRect window = viewport->GetScreenRect();
		rMatrixUtil::Ortho2D(window.Left(), window.Right(), window.Bottom(), window.Top(), matrixOrtho2D);

		m_engine.renderer->Begin(matrixOrtho2D, identity);
		m_uiManager->Draw(viewport);
		m_engine.renderer->End();
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
	m_module->Init(args);
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