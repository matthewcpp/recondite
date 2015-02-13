#ifndef RI_ACTORLOADER_HPP
#define RI_ACTORLOADER_HPP

#include "rBuild.hpp"

#include "xml/rXMLElement.hpp"
#include "xml/rXMLUtil.hpp"
#include "rActor3.hpp"
#include "interface/riSerialization.hpp"

class rEngine;
class rActor3;

class RECONDITE_API riActorLoader{
public:
	virtual rActor3* LoadActor(rXMLElement* element, const rString& id, rEngine* engine) = 0;

protected:
	void LoadActorProperties(rXMLElement* element, rActor3* actor);
};

class RECONDITE_API riActorSerializer{
public:
	virtual bool SerializeActor(rActor3* actor, riSerializationTarget* target) = 0;

};

#endif