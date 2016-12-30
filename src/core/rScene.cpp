#include "rScene.hpp"

rScene::rScene(rEngine* engine){
	m_isLoading = false;

	m_engine = engine;
}

rScene::~rScene(){
	Clear();
}

void rScene::Update(){
	rActorMap::iterator end = m_actors.end();

	for (rActorMap::iterator it = m_actors.begin(); it != end; ++it){
		it->second->Update();
	}

	Flush();
}

void rScene::Draw(){
	//todo: view frustrum culling
	rActorMap::iterator end = m_actors.end();

	for (rActorMap::iterator it = m_actors.begin(); it != end; ++it) {
		if (it->second->IsDrawable()) {
			m_engine->renderer->Add((rDrawable*)it->second);
		}
	}
		
}

bool rScene::RenameActor(const rString& oldId, const rString& newId){
	if (m_actors.count(oldId) == 0 || m_actors.count(newId) == 1)
		return false;

	rActor3* actor = m_actors[oldId];
	actor->SetId(newId);
	m_actors.erase(oldId);
	m_actors[newId] = actor;

	rActor3RenameEvent event(actor, oldId);
	Trigger(rEVT_SCENE_ACTOR_RENAMED, event);

	return true;
}

bool rScene::AddActor(rActor3* actor){
	rString name = actor->Id();

	if (m_actors.count(name)) {
		return false;
	}
	else {
		m_actors[name] = actor;

		if (!m_isLoading) {
			rActor3Event event(actor);
			Trigger(rEVT_SCENE_ACTOR_ADDED, event);
		}

		return true;
	}
}

rActor3* rScene::GetActor(const rString& name) const{
	rActor3* actor = nullptr;

	rActorMap::const_iterator result = m_actors.find(name);

	if (result != m_actors.end())
		actor = result->second;

	return actor;
}

void rScene::DeleteActor(rActor3* actor) {
	m_ActorsToDelete.insert(actor);
}

void rScene::Flush() {
	for (rActor3* actor : m_ActorsToDelete) {
		rActor3Event event(actor);
		Trigger(rEVT_SCENE_ACTOR_REMOVED, event);

		m_actors.erase(actor->Id());
		actor->OnDelete();
		delete actor;
	}

	m_ActorsToDelete.clear();
}

void rScene::DeleteActors(std::function<bool(rActor3*)> shouldDelete){
	for (auto it = m_actors.cbegin(); it != m_actors.cend();){
		if (shouldDelete(it->second)){
			it->second->OnDelete();
			delete it->second;
			m_actors.erase(it++);
		}
		else{
			++it;
		}
	}
}

void rScene::Clear(){
	rActorMap::iterator end = m_actors.end();

	for (rActorMap::iterator it = m_actors.begin(); it != end; ++it){
		it->second->OnDelete();
		delete it->second;
	}
	
	m_actors.clear();
}

rAlignedBox3 rScene::GetBounding() {
	rAlignedBox3 bounding;
	rActorMap::iterator end = m_actors.end();

	for (rActorMap::iterator it = m_actors.begin(); it != end; ++it) {
		riBoundingVolume* boundingVolume = it->second->BoundingVolume();
		if (boundingVolume) bounding.AddBox(boundingVolume->FitBox());
	}

	return bounding;
}


size_t rScene::NumActors () const{
	return m_actors.size();
}

rString rScene::GetDefaultActorId(const rString& prefix){
	rString defaultActorId;
	int count = 0;

	do {
		rOStringStream str(prefix);
		str << count;
		defaultActorId = str.Str();
		count += 1;
	}while(m_actors.count(defaultActorId) == 1);

	return defaultActorId;
}

void rScene::RayPick(const rRay3& ray, rPickResult& pickResult) {
	rPickResult currentResult, bestResult;
	float selectedActorDistance = FLT_MAX;

	rActorMap::iterator end = m_actors.end();
	for (rActorMap::iterator it = m_actors.begin(); it != end; ++it) {
		rActor3* currentActor = it->second;

		if (!currentActor->Pickable()) { 
			continue; 
		}

		currentActor->RayPick(ray, currentResult);
		if (currentResult.hit && currentResult.distanceSquared < selectedActorDistance) {
			bestResult = currentResult;
			selectedActorDistance = currentResult.distanceSquared;
		}
	}

	pickResult = bestResult;
}

bool rScene::Save(riSerializationTarget* target){
	riSerializationTarget* actorTarget = target->SubObject("actors");

	for (auto& actor : m_actors) {
		actor.second->Save(actorTarget);
	}

	return true;
}

bool rScene::Load(riSerializationTarget* target){
	m_isLoading = true;
	rEvent event;
	Trigger(rEVT_SCENE_LOAD_BEGIN, event);

	ParseActors(target);

	m_isLoading = false;
	Trigger(rEVT_SCENE_LOAD_END, event);

	return true;
}
bool rScene::ParseActors(riSerializationTarget* target){
	riSerializationTarget* actorsTarget = target->SubObject("actors");
	riSerializationTarget* actorTarget = actorsTarget->SubObject("actor");

	if (actorTarget){
		rString className, id;

		do{
			actorTarget->String("class", className);
			actorTarget->String("id", id);

			rActor3* actor = m_engine->actors->GetActorClass(className, m_engine, id);
			if (actor){
				actor->Load(actorTarget);
				AddActor(actor);
			}
			else{
				Log::Warning("Unable to load actor with class: " + className);
			}
		} while (actorTarget->Next());
	}

	return true;
}

bool rScene::IsLoading() const{
	return m_isLoading;
}

void rScene::GetActors(rArrayString& names) const{
	for (auto& entry : m_actors)
		names.push_back(entry.first);
}