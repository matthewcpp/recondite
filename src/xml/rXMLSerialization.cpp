#include "xml/rXMLSerialization.hpp"

rXMLSerializationTarget::rXMLSerializationTarget(rXMLElement* element){
	m_element = element;
}

rXMLSerializationTarget::~rXMLSerializationTarget(){
	for (auto target : m_targets)
		delete target;
}

bool rXMLSerializationTarget::SetBoolProperty(const rString& name, bool& val){
	m_element->CreateChild(name, val);
	return true;
}

bool rXMLSerializationTarget::SetIntProperty(const rString& name, int& val){
	m_element->CreateChild(name, val);
	return true;
}

bool rXMLSerializationTarget::SetFloatProperty(const rString& name, float& val){
	m_element->CreateChild(name, val);
	return true;
}

bool rXMLSerializationTarget::SetStringProperty(const rString& name, const rString& val){
	m_element->CreateChild(name, val);
	return true;
}

bool rXMLSerializationTarget::SetVector3Property(const rString& name, const rVector3& val){
	rXMLElement* element = m_element->CreateChild(name);

	element->AddAttribute("x", val.x);
	element->AddAttribute("y", val.y);
	element->AddAttribute("z", val.z);

	return true;
}

bool rXMLSerializationTarget::SetColorProperty(const rString& name, const rColor& val){
	rXMLElement* element = m_element->CreateChild(name);

	element->AddAttribute("r", (int)val.red);
	element->AddAttribute("g", (int)val.green);
	element->AddAttribute("b", (int)val.blue);
	element->AddAttribute("a", (int)val.alpha);

	return true;
}

rXMLSerializationTarget* rXMLSerializationTarget::CreateChildObject(const rString& name){
	rXMLElement* child = m_element->CreateChild(name);
	rXMLSerializationTarget* newTarget = new rXMLSerializationTarget(child);
	m_targets.push_back(newTarget);

	return newTarget;
}


///-------------------------------


rXMLSerializationSource::rXMLSerializationSource(rXMLElement* element){
	m_element = element;
}

rXMLSerializationSource::~rXMLSerializationSource(){
	for (auto source : m_sources)
		delete source;
}

bool rXMLSerializationSource::GetBoolProperty(const rString& name, bool& val) const{
	rXMLElement* element = m_element->GetFirstChildNamed(name);

	if (element){
		int i;
		element->GetText(i);
		val = (i == 1);
		return true;
	}

	return false;
}

bool rXMLSerializationSource::GetIntProperty(const rString& name, int& val) const{
	rXMLElement* element = m_element->GetFirstChildNamed(name);

	if (element){
		element->GetText(val);
		return true;
	}

	return false;
}

bool rXMLSerializationSource::GetFloatProperty(const rString& name, float& val) const{
	rXMLElement* element = m_element->GetFirstChildNamed(name);

	if (element){
		element->GetText(val);
		return true;
	}

	return false;
}

bool rXMLSerializationSource::GetStringProperty(const rString& name, rString& val) const{
	rXMLElement* element = m_element->GetFirstChildNamed(name);

	if (element){
		element->GetText(val);
		return true;
	}

	return false;
}

bool rXMLSerializationSource::GetVector3Property(const rString& name, rVector3& val) const{
	rXMLElement* element = m_element->GetFirstChildNamed(name);

	if (element){
		element->GetAttribute<float>("x", val.x);
		element->GetAttribute<float>("y", val.y);
		element->GetAttribute<float>("z", val.z);
		return true;
	}

	return false;
}

bool rXMLSerializationSource::GetColorProperty(const rString& name, rColor& val) const{
	rXMLElement* element = m_element->GetFirstChildNamed(name);

	if (element){
		int r, g, b, a;
		element->GetAttribute<int>("r", r);
		element->GetAttribute<int>("g", g);
		element->GetAttribute<int>("b", b);
		element->GetAttribute<int>("a", a);

		val.Set((unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a);

		return true;
	}

	return false;
}

riSerializationSource* rXMLSerializationSource::GetChildObject(const rString& name){
	rXMLElement* child = m_element->GetFirstChildNamed(name);
	rXMLSerializationSource* childSource = new rXMLSerializationSource(child);
	m_sources.push_back(childSource);

	return childSource;
}