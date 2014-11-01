#include "rScene.hpp"

void rScene::Update(rEngine& engine){
	rActorArray actorsToDelete;
	rActorMap::iterator end = m_actors.end();
	int remove;

	for (rActorMap::iterator it = m_actors.begin(); it != end; ++it){
		remove = it->second->Update(engine);

		if (remove)
			actorsToDelete.push_back(it->second);
	}

	for (size_t i = 0; i < actorsToDelete.size(); i++)
		DeleteActor(actorsToDelete[i]->Name());
}

void rScene::Draw(rEngine& engine){
	//todo: view frustrum culling
	rActorMap::iterator end = m_actors.end();

	for (rActorMap::iterator it = m_actors.begin(); it != end; ++it)
		it->second->Draw(engine);
}

void rScene::AddActor(rActor3* actor){
	rString name = actor->Name();
	
	if (m_actors.count(name)){
		DeleteActor(name);
	}

	m_actors[name] = actor;

}

rActor3* rScene::GetActor(const rString& name) const{
	rActor3* actor = NULL;

	rActorMap::const_iterator result = m_actors.find(name);

	if (result != m_actors.end())
		actor = result->second;

	return actor;
}

void rScene::DeleteActor(const rString& name){
	rActorMap::iterator result = m_actors.find(name);

	if (result != m_actors.end()){
		delete result->second;
		m_actors.erase(result);
	}
}

void rScene::Clear(){
	rActorMap::iterator end = m_actors.end();

	for (rActorMap::iterator it = m_actors.begin(); it != end; ++it)
		delete it->second;

	m_actors.clear();
}

size_t rScene::NumActors () const{
	return m_actors.size();
}

void rScene::RegisterActorLoader(const rString& className, riActorLoader* actorLoader){
	UnregisterActorLoader(className);

	m_actorLoaders[className] = actorLoader;
}

void rScene::UnregisterActorLoader(const rString& className){
	rActorLoaderMap::iterator it = m_actorLoaders.find(className);

	if (it != m_actorLoaders.end()){
		delete it->second;
		m_actorLoaders.erase(it);
	}
}

bool rScene::LoadScene(rIStream& stream){
	rXMLDocument document;
	document.LoadFromStream(stream);

	rXMLElement* sceneRoot = document.GetRoot();

	if (!sceneRoot) return false;

	for (size_t i = 0; i < sceneRoot->NumChildren(); i++){
		rXMLElement* actorElement = sceneRoot->GetChild(i);

		rString elementName = actorElement->Name();
		rString id;
		actorElement->GetAttribute<rString>("id", id);

		if (m_actorLoaders.count(elementName)){
			rActor3* actor = m_actorLoaders[elementName]->LoadActor(actorElement, id);
			if (actor) AddActor(actor);
		}
		else{
			rLog::Warning("Unable to Load Level element: " + elementName);
		}
	}

	return true;
}