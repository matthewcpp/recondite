#ifndef R_XMLSERIALIZATION_HPP
#define R_XMLSERIALIZATION_HPP

#include <vector>

#include "rBuild.hpp"

#include "interface/riSerialization.hpp"

#include "rXMLElement.hpp"

class RECONDITE_API rXMLSerializationTarget : public riSerializationTarget{
public:
	rXMLSerializationTarget(rXMLElement* element);
	~rXMLSerializationTarget();

	virtual bool SetBoolProperty(const rString& name, bool& val);
	virtual bool SetIntProperty(const rString& name, int& val);
	virtual bool SetFloatProperty(const rString& name, float& val);
	virtual bool SetStringProperty(const rString& name, const rString& val);
	virtual bool SetVector3Property(const rString& name, const rVector3& val);
	virtual bool SetColorProperty(const rString& name, const rColor& val);

	virtual rXMLSerializationTarget* CreateChildObject(const rString& name);

private:
	rXMLElement* m_element;

	std::vector<rXMLSerializationTarget*> m_targets;

	rNO_COPY_CLASS(rXMLSerializationTarget)
};


class RECONDITE_API rXMLSerializationSource : public riSerializationSource{
public:
	rXMLSerializationSource(rXMLElement* element);
	~rXMLSerializationSource();

	virtual bool GetBoolProperty(const rString& name, bool& val) const ;
	virtual bool GetIntProperty(const rString& name, int& val) const;
	virtual bool GetFloatProperty(const rString& name, float& val) const;
	virtual bool GetStringProperty(const rString& name, rString& val) const;
	virtual bool GetVector3Property(const rString& name, rVector3& val) const;
	virtual bool GetColorProperty(const rString& name, rColor& color) const;

	virtual riSerializationSource* GetChildObject(const rString& name);

private:
	rXMLElement* m_element;

	std::vector<rXMLSerializationSource*> m_sources;

	rNO_COPY_CLASS(rXMLSerializationSource)
};

#endif