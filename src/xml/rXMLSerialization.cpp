#include "xml/rXMLSerialization.hpp"

rXMLSerializationTarget::rXMLSerializationTarget(rXMLElement* element){
	m_element = element;
}

rXMLSerializationTarget::~rXMLSerializationTarget(){
	for (auto target : m_targets)
		delete target;
}

bool rXMLSerializationTarget::Boolean(const rString& name, bool& val){
	m_element->CreateChild(name, val);
	return true;
}

bool rXMLSerializationTarget::Int(const rString& name, int& val){
	m_element->CreateChild(name, val);
	return true;
}

bool rXMLSerializationTarget::Float(const rString& name, float& val){
	m_element->CreateChild(name, val);
	return true;
}

bool rXMLSerializationTarget::String(const rString& name, rString& val){
	m_element->CreateChild(name, val);
	return true;
}

bool rXMLSerializationTarget::Vector3(const rString& name, rVector3& val){
	rXMLElement* element = m_element->CreateChild(name);

	element->AddAttribute("x", val.x);
	element->AddAttribute("y", val.y);
	element->AddAttribute("z", val.z);

	return true;
}

bool rXMLSerializationTarget::Color(const rString& name, rColor& val){
	rXMLElement* element = m_element->CreateChild(name);

	element->AddAttribute("r", (int)val.red);
	element->AddAttribute("g", (int)val.green);
	element->AddAttribute("b", (int)val.blue);
	element->AddAttribute("a", (int)val.alpha);

	return true;
}

rXMLSerializationTarget* rXMLSerializationTarget::SubObject(const rString& name){
	rXMLElement* child = m_element->CreateChild(name);
	rXMLSerializationTarget* newTarget = new rXMLSerializationTarget(child);
	m_targets.push_back(newTarget);

	return newTarget;
}

bool rXMLSerializationTarget::Next(){
	return false;
}

bool rXMLSerializationTarget::Category(const rString& name){
	return false;
}


///-------------------------------


rXMLSerializationSource::rXMLSerializationSource(rXMLElement* element){
	m_element = element;
	m_index = 0;
}

rXMLSerializationSource::~rXMLSerializationSource(){
	for (auto source : m_sources)
		delete source;
}

bool rXMLSerializationSource::Boolean(const rString& name, bool& val){
	rXMLElement* element = m_element->GetFirstChildNamed(name);

	if (element){
		int i;
		element->GetText(i);
		val = (i == 1);
		return true;
	}

	return false;
}

bool rXMLSerializationSource::Int(const rString& name, int& val){
	rXMLElement* element = m_element->GetFirstChildNamed(name);

	if (element){
		element->GetText(val);
		return true;
	}

	return false;
}

bool rXMLSerializationSource::Float(const rString& name, float& val){
	rXMLElement* element = m_element->GetFirstChildNamed(name);

	if (element){
		element->GetText(val);
		return true;
	}

	return false;
}

bool rXMLSerializationSource::String(const rString& name, rString& val){
	rXMLElement* element = m_element->GetFirstChildNamed(name);

	if (element){
		element->GetText(val);
		return true;
	}

	return false;
}

bool rXMLSerializationSource::Vector3(const rString& name, rVector3& val){
	rXMLElement* element = m_element->GetFirstChildNamed(name);

	if (element){
		element->GetAttribute<float>("x", val.x);
		element->GetAttribute<float>("y", val.y);
		element->GetAttribute<float>("z", val.z);
		return true;
	}

	return false;
}

bool rXMLSerializationSource::Color(const rString& name, rColor& val){
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

riSerializationTarget* rXMLSerializationSource::SubObject(const rString& name){
	rXMLElement* child = m_element->GetFirstChildNamed(name);
	rXMLSerializationSource* childSource = nullptr;

	if (child){
		childSource = new rXMLSerializationSource(child);
		m_sources.push_back(childSource);
	}

	return childSource;
}

bool rXMLSerializationSource::Next(){
	rXMLElement* parent = m_element->Parent();

	if (parent){
		m_index++;
		if (m_index < parent->NumChildren()){
			m_element = parent->GetChild(m_index);
			return true;
		}
	}
	return nullptr;
}

bool rXMLSerializationSource::Category(const rString& name){
	return false;
}