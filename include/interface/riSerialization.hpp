#ifndef RI_SERIALIZATION_HPP
#define RI_SERIALIZATION_HPP

#include "rBuild.hpp"
#include "rDefs.hpp"
#include "rString.hpp"

#include "rVector3.hpp"
#include "rColor.hpp"

class RECONDITE_API riSerializationTarget{
public:
	virtual bool SetBoolProperty(const rString& name, bool& val) = 0;
	virtual bool SetIntProperty(const rString& name, int& val) = 0;
	virtual bool SetFloatProperty(const rString& name, float& val) = 0;
	virtual bool SetStringProperty(const rString& name, const rString& val) = 0;
	virtual bool SetVector3Property(const rString& name, const rVector3& val) = 0;
	virtual bool SetColorProperty(const rString& name, const rColor& color) = 0;

	virtual riSerializationTarget* CreateChildObject(const rString& name) = 0;
};

class RECONDITE_API riSerializationSource{
public:
	virtual bool GetBoolProperty(const rString& name, bool& val) const = 0;
	virtual bool GetIntProperty(const rString& name, int& val) const = 0;
	virtual bool GetFloatProperty(const rString& name, float& val) const = 0;
	virtual bool GetStringProperty(const rString& name, rString& val) const = 0;
	virtual bool GetVector3Property(const rString& name, rVector3& val) const = 0;
	virtual bool GetColorProperty(const rString& name, rColor& color) const = 0;

	virtual riSerializationSource* GetChildObject(const rString& name) = 0;
	
};
#endif