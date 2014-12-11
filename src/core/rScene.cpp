#include "rScene.hpp"

void rScene::Update(rEngine& engine){
	rActorArray actorsToDelete;
	rActorMap::iterator end = m_actors.end();
	int remove;

	for (rActorMap::iterator it = m_actors.begin(); it != end; ++it){
		remove = it->second->Update();

		if (remove)
			actorsToDelete.push_back(it->second);
	}

	for (size_t i = 0; i < actorsToDelete.size(); i++)
		DeleteActor(actorsToDelete[i]->Id());
}

void rScene::Draw(rEngine& engine){
	//todo: view frustrum culling
	rActorMap::iterator end = m_actors.end();

	for (rActorMap::iterator it = m_actors.begin(); it != end; ++it)
		it->second->Draw();
}

void rScene::AddActor(rActor3* actor){
	rString name = actor->Id();
	
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

rActor3* rScene::RayPick(const rRay3& ray){
	rActor3* selectedActor = NULL;
	float selectedActorDistance = FLT_MAX;
	rVector3 selectionPoint;
	

	rActorMap::iterator end = m_actors.end();
	for (rActorMap::iterator it = m_actors.begin(); it != end; ++it){
		rActor3* currentActor = it->second;
		riBoundingVolume* boundingVolume = currentActor->BoundingVolume();

		if (boundingVolume && boundingVolume->IntersectsRay(ray, &selectionPoint)){
			float currentActorDistance = ray.origin.Distance(selectionPoint);
			if (currentActorDistance < selectedActorDistance){
				selectedActor = currentActor;
				selectedActorDistance = currentActorDistance;
			}
		}
	}

	return selectedActor;
}