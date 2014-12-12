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

void rApplicationBase::InitEngine(rGraphicsDevice* graphics, rContentManager* content, rInputManager* input){
	m_graphicsDevice = graphics; 

	m_overlayManager = new ruiOverlayManager(&m_engine);
	input->SetUI(m_overlayManager);

	m_engine.application = this;

	m_engine.ui = m_overlayManager;
	m_engine.content = content;
	m_engine.input = input;
	m_engine.renderer = new rRenderer(graphics, content);
	m_engine.time.Start(GetTimeMiliseconds());

	m_scene = new rScene(this, m_graphicsDevice);
	m_engine.scene = m_scene;

	m_isRunning = true;

	m_graphicsDevice->Init();
	m_engine.content->InitDefaultAssets();
	m_engine.renderer->CreateRequiredMaterials();
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

rViewport* rApplicationBase::CreateViewport(const rString& name){
	if (m_viewports.count(name)){
		return NULL;
	}
	else {
		rViewport* viewport = new rViewport(name);
		m_viewports[name] = viewport;
		return viewport;
	}
}

rViewport* rApplicationBase::GetViewport(const rString& name) const{
	rViewportMap::const_iterator it = m_viewports.find(name);

	if (it != m_viewports.end()){
		return it->second;
	}
	else{
		return NULL;
	}
}

void rApplicationBase::DeleteViewport(const rString& name){
	rViewportMap::iterator it = m_viewports.find(name);

	if (it != m_viewports.end()){
		delete it->second;
		m_viewports.erase(it);
	}
}

size_t rApplicationBase::NumViewports() const{
	return m_viewports.size();
}

size_t rApplicationBase::FrameCount() const{
	return m_frameCount;
}

bool rApplicationBase::Init(){
	return true;
}

void rApplicationBase::Uninit(){
	m_module->Uninit(m_engine);
	rLog::Shutdown();
}

void rApplicationBase::LoadScene(const rString& name){
	rIAssetStream stream = m_engine.content->LoadTextFromPath(name);
	
	if (stream){
		m_scene->Clear();

		rXMLDocument document;
		document.LoadFromStream(*stream);

		rXMLElement* sceneRoot = document.GetRoot();

		if (!sceneRoot) return;

		for (size_t i = 0; i < sceneRoot->NumChildren(); i++){
			rXMLElement* actorElement = sceneRoot->GetChild(i);

			rString elementName = actorElement->Name();
			rString id;
			if (!actorElement->GetAttribute<rString>("id", id))
				id = m_scene->GetDefaultActorId(elementName);

			if (m_actorLoaders.count(elementName)){
				rActor3* actor = m_actorLoaders[elementName]->LoadActor(actorElement, id, &m_engine);
				if (actor) m_scene->AddActor(actor);
			}
			else{
				rLog::Warning("Unable to Load Level element: " + elementName);
			}
		}
	}
}

void rApplicationBase::RegisterActorLoader(const rString& className, riActorLoader* actorLoader){
	UnregisterActorLoader(className);

	m_actorLoaders[className] = actorLoader;
}

void rApplicationBase::UnregisterActorLoader(const rString& className){
	rActorLoaderMap::iterator it = m_actorLoaders.find(className);

	if (it != m_actorLoaders.end()){
		delete it->second;
		m_actorLoaders.erase(it);
	}
}