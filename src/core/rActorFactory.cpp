#include "rActorFactory.hpp"

bool rActorFactory::AddActorClass(const rString& name, ActorFunction func){
	m_actorClasses[name] = func;
	return true;
}

rActor3* rActorFactory::GetActorClass(const rString& name, rEngine* engine, const rString& id){
	if (m_actorClasses.count(name))
		return m_actorClasses[name](engine, id);
	else
		return nullptr;
}