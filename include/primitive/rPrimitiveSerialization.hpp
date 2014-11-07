#ifndef R_PRIMITIVESERIZALIZATION_HPP
#define R_PRIMITIVESERIZALIZATION_HPP

#include "rBuild.hpp"

#include "rActorSerialization.hpp"
#include "xml/rXMLUtil.hpp"

#include "primitive/rPrimitiveBox.hpp"
#include "primitive/rPrimitiveCone.hpp"
#include "primitive/rPrimitiveCylinder.hpp"

//---------- Box ----------

class RECONDITE_API rPrimitiveBoxReader : public riActorLoader{
public:
	virtual rActor3* LoadActor(rXMLElement* element, const rString& id, rEngine* engine);
};

//---------- Cone ----------

class RECONDITE_API rPrimitiveConeReader : public riActorLoader{
public:
	virtual rActor3* LoadActor(rXMLElement* element, const rString& id, rEngine* engine);
};

//---------- Cylinder ----------

class RECONDITE_API rPrimitiveCylinderReader : public riActorLoader{
public:
	virtual rActor3* LoadActor(rXMLElement* element, const rString& id, rEngine* engine);
};

#endif