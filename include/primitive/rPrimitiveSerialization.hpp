#ifndef R_PRIMITIVESERIZALIZATION_HPP
#define R_PRIMITIVESERIZALIZATION_HPP

#include "rBuild.hpp"

#include "rActorSerialization.hpp"
#include "xml/rXMLUtil.hpp"

#include "primitive/rPrimitiveBox.hpp"
#include "primitive/rPrimitiveCone.hpp"
#include "primitive/rPrimitiveCylinder.hpp"
#include "primitive/rPrimitiveSphere.hpp"

//---------- Primitive ----------

class RECONDITE_API rPrimitiveReader : public riActorLoader{
protected:
	void LoadPrimitiveProperties(rXMLElement* element, rPrimitive* primitive);
};

//---------- Box ----------

class RECONDITE_API rPrimitiveBoxReader : public rPrimitiveReader{
public:
	virtual rActor3* LoadActor(rXMLElement* element, const rString& id, rEngine* engine);
};

//---------- Cone ----------

class RECONDITE_API rPrimitiveConeReader : public rPrimitiveReader{
public:
	virtual rActor3* LoadActor(rXMLElement* element, const rString& id, rEngine* engine);
};

//---------- Cylinder ----------

class RECONDITE_API rPrimitiveCylinderReader : public rPrimitiveReader{
public:
	virtual rActor3* LoadActor(rXMLElement* element, const rString& id, rEngine* engine);
};

//---------- Sphere ----------
class RECONDITE_API rPrimitiveSphereReader : public rPrimitiveReader{
public:
	virtual rActor3* LoadActor(rXMLElement* element, const rString& id, rEngine* engine);
};
#endif