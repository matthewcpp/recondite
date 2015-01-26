#include "rComponent.hpp"

rComponent::rComponent(){
	m_isReady = false;
}

bool rComponent::Init(){
	return true;
}

void rComponent::Uninit(){
	rLog::Shutdown();
}

void rComponent::LoadScene(const rString& name){
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

void rComponent::RegisterActorLoader(const rString& className, riActorLoader* actorLoader){
	UnregisterActorLoader(className);

	m_actorLoaders[className] = actorLoader;
}

void rComponent::UnregisterActorLoader(const rString& className){
	rActorLoaderMap::iterator it = m_actorLoaders.find(className);

	if (it != m_actorLoaders.end()){
		delete it->second;
		m_actorLoaders.erase(it);
	}
}

void rComponent::InitEngine(rGraphicsDevice* graphics, rContentManager* content, rInputManager* input){
	m_graphicsDevice = graphics;

	m_overlayManager = new ruiOverlayManager(&m_engine);
	input->SetUI(m_overlayManager);

	m_engine.component = this;

	m_engine.ui = m_overlayManager;
	m_engine.content = content;
	m_engine.input = input;
	m_engine.renderer = new rRenderer(graphics, content);
	m_engine.time.Start(GetTimeMiliseconds());

	m_scene = new rScene(this, m_graphicsDevice);
	m_engine.scene = m_scene;

	m_graphicsDevice->Init();
	m_engine.content->InitDefaultAssets();
	m_engine.renderer->CreateRequiredMaterials();

	m_isReady = true;
}

rViewport* rComponent::CreateViewport(const rString& name){
	if (m_viewports.count(name)){
		return NULL;
	}
	else {
		rViewport* viewport = new rViewport(name);
		m_viewports[name] = viewport;
		return viewport;
	}
}

rViewport* rComponent::GetViewport(const rString& name) const{
	rViewportMap::const_iterator it = m_viewports.find(name);

	if (it != m_viewports.end()){
		return it->second;
	}
	else{
		return NULL;
	}
}

void rComponent::DeleteViewport(const rString& name){
	rViewportMap::iterator it = m_viewports.find(name);

	if (it != m_viewports.end()){
		delete it->second;
		m_viewports.erase(it);
	}
}

size_t rComponent::NumViewports() const{
	return m_viewports.size();
}

bool rComponent::IsReady() const{
	return m_isReady;
}