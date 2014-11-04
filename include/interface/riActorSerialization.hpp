#ifndef RI_ACTORLOADER_HPP
#define RI_ACTORLOADER_HPP

#include "rBuild.hpp"

#include "xml/rXMLElement.hpp"

class rActor3;
class rEngine;

class RECONDITE_API riActorLoader{
public:
	virtual rActor3* LoadActor(rXMLElement* element, const rString& id, rEngine* engine) = 0;
};

class RECONDITE_API riActorSerializer{
public:
	virtual bool SerializeActor(rActor3* actor, rXMLElement* element) = 0;
};

#endif