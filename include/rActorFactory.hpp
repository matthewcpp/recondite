#ifndef R_ACTORFACTORY_HPP
#define R_ACTORFACTORY_HPP

#include <functional>
#include <map>

#include "rBuild.hpp"
#include "rString.hpp"

class rEngine;
class rActor3;

class RECONDITE_API rActorFactory{
public:
	typedef std::function<rActor3* (rEngine*, const rString&)> ActorFunction;

public:
	bool AddActorClass(const rString& name, ActorFunction func);
	rActor3* GetActorClass(const rString& name, rEngine* engine, const rString& id);

private:
	typedef std::map<rString, ActorFunction> rActorClassMap;

private:
	rActorClassMap m_actorClasses;
};

#endif