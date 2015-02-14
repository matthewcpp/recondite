#ifndef RI_SERIALIZATION_HPP
#define RI_SERIALIZATION_HPP

#include "rBuild.hpp"
#include "rDefs.hpp"
#include "rString.hpp"

#include "rVector3.hpp"
#include "rColor.hpp"

class RECONDITE_API riSerializationTarget{
public:
	virtual bool Bool(const rString& name, bool& val) = 0;
	virtual bool Int(const rString& name, int& val) = 0;
	virtual bool Float(const rString& name, float& val) = 0;
	virtual bool String(const rString& name, rString& val) = 0;
	virtual bool Vector3(const rString& name, rVector3& val) = 0;
	virtual bool Color(const rString& name, rColor& color) = 0;

	virtual riSerializationTarget* SubObject(const rString& name) = 0;
	virtual riSerializationTarget* GetNextObject() = 0;
};

class RECONDITE_API riSerializable{
public:
	virtual bool Serialize(riSerializationTarget* target) = 0;
};
#endif