#ifndef R_PRIMITIVESERIZALIZATION_HPP
#define R_PRIMITIVESERIZALIZATION_HPP

#include "rBuild.hpp"

#include "interface/riActorSerialization.hpp"
#include "xml/rXMLUtil.hpp"

#include "rPrimitiveBox.hpp"
#include "rPrimitiveCone.hpp"

//---------- Box ----------

class RECONDITE_API rPrimitiveBoxReader : public riActorLoader{
public:
	virtual rActor3* LoadActor(rXMLElement* element, const rString& id, rEngine* engine);
};

class RECONDITE_API rPrimitiveBoxWriter{
private:
	virtual bool SerializeActor(rActor3* actor, rXMLElement* element);
};

//---------- Cone ----------

class RECONDITE_API rPrimitiveConeReader : public riActorLoader{
public:
	virtual rActor3* LoadActor(rXMLElement* element, const rString& id, rEngine* engine);
};

#endif