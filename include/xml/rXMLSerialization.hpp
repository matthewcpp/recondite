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

	virtual bool Boolean(const rString& name, bool& val);
	virtual bool Int(const rString& name, int& val);
	virtual bool Float(const rString& name, float& val);
	virtual bool String(const rString& name, rString& val);
	virtual bool Vector3(const rString& name, rVector3& val);
	virtual bool Color(const rString& name, rColor& val);

	virtual bool Category(const rString& name);

	virtual rXMLSerializationTarget* SubObject(const rString& name);
	virtual bool Next();

private:
	rXMLElement* m_element;

	std::vector<rXMLSerializationTarget*> m_targets;

	rNO_COPY_CLASS(rXMLSerializationTarget)
};


class RECONDITE_API rXMLSerializationSource : public riSerializationTarget{
public:
	rXMLSerializationSource(rXMLElement* element);
	~rXMLSerializationSource();

	virtual bool Boolean(const rString& name, bool& val);
	virtual bool Int(const rString& name, int& val);
	virtual bool Float(const rString& name, float& val);
	virtual bool String(const rString& name, rString& val);
	virtual bool Vector3(const rString& name, rVector3& val);
	virtual bool Color(const rString& name, rColor& color);

	virtual bool Category(const rString& name);

	virtual riSerializationTarget* SubObject(const rString& name);
	virtual bool Next();

private:
	rXMLElement* m_element;
	size_t m_index;

	std::vector<rXMLSerializationSource*> m_sources;

	rNO_COPY_CLASS(rXMLSerializationSource)
};

#endif