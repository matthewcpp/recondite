#include "rPropertyCollection.hpp"

rPropertyCollection::~rPropertyCollection(){
	Clear();
}

void rPropertyCollection::SetBool(const rString& key, bool val){
	DeleteProperty(key);
	m_properties[key] = new rProperty(val);
}

bool rPropertyCollection::GetBool(const rString& key, bool& val) const{
	rPropertyMap::const_iterator p = m_properties.find(key);

	if (p != m_properties.end()){
		val = p->second->value.boolVal;
		return true;
	}
	else{
		return false;
	}
}

void rPropertyCollection::SetInt(const rString& key, int val){
	DeleteProperty(key);
	m_properties[key] = new rProperty(val);
}

bool rPropertyCollection::GetInt(const rString& key, int& val) const{
	rPropertyMap::const_iterator p = m_properties.find(key);

	if (p != m_properties.end() && p->second->type == rPROPERTY_TYPE_INT){
		val = p->second->value.intVal;
		return true;
	}
	else{
		return false;
	}
}

void rPropertyCollection::SetFloat(const rString& key, float val){
	DeleteProperty(key);
	m_properties[key] = new rProperty(val);
}

bool rPropertyCollection::GetFloat(const rString& key, float& val) const{
	rPropertyMap::const_iterator p = m_properties.find(key);

	if (p != m_properties.end() && p->second->type == rPROPERTY_TYPE_FLOAT){
		val = p->second->value.floatVal;
		return true;
	}
	else{
		return false;
	}
}

void rPropertyCollection::DeleteProperty(const rString& key){
	rPropertyMap::iterator p = m_properties.find(key);

	if (p != m_properties.end()){
		delete p->second;
		m_properties.erase(p);
	}
}

void rPropertyCollection::SetString(const rString& key, const rString& val){
	DeleteProperty(key);
	m_properties[key] = new rProperty(val);
}

bool rPropertyCollection::GetString(const rString& key, rString& val){
	rPropertyMap::const_iterator p = m_properties.find(key);

	if (p != m_properties.end() && p->second->type == rPROPERTY_TYPE_STRING){
		val = *(p->second->value.stringVal);
		return true;
	}
	else{
		return false;
	}
}

void rPropertyCollection::SetColor(const rString& key, const rColor& val) {
	DeleteProperty(key);
	m_properties[key] = new rProperty(val);
}

bool rPropertyCollection::GetColor(const rString& key, rColor& val) const {
	rPropertyMap::const_iterator p = m_properties.find(key);

	if (p != m_properties.end() && p->second->type == rPROPERTY_TYPE_COLOR){
		val = *(p->second->value.colorVal);
		return true;
	}
	else{
		return false;
	}
}

void rPropertyCollection::SetFont(const rString& key, rFont* val){
	DeleteProperty(key);
	m_properties[key] = new rProperty(val);
}

rFont* rPropertyCollection::GetFont(const rString& key) const{
	rPropertyMap::const_iterator p = m_properties.find(key);

	if (p != m_properties.end()  && p->second->type == rPROPERTY_TYPE_FONT)
		return p->second->value.fontVal;
	else
		return NULL;
}

void rPropertyCollection::SetTexture(const rString& key, rTexture2D* val){
	DeleteProperty(key);
	m_properties[key] = new rProperty(val);
}

rTexture2D* rPropertyCollection::GetTexture(const rString& key) const{
	rPropertyMap::const_iterator p = m_properties.find(key);

	if (p != m_properties.end()  && p->second->type == rPROPERTY_TYPE_TEXTURE)
		return p->second->value.textureVal;
	else
		return NULL;
}

size_t rPropertyCollection::NumProperties() const{
	return m_properties.size();
}

void rPropertyCollection::Clear(){
	rPropertyMap::iterator end = m_properties.end();

	for (rPropertyMap::iterator it = m_properties.begin(); it != end; ++it)
		delete it->second;

	m_properties.clear();
}

//------------------------
rProperty::rProperty(bool b){
	type = rPROPERTY_TYPE_BOOL;
	value.boolVal = b;
}

rProperty::rProperty(int i){
	type = rPROPERTY_TYPE_INT;
	value.intVal = i;
}

rProperty::rProperty(float f){
	type = rPROPERTY_TYPE_FLOAT;
	value.floatVal = f;
}

rProperty::rProperty(const rString& s){
	type = rPROPERTY_TYPE_STRING;
	value.stringVal = new rString(s);
}

rProperty::rProperty(const rColor& c){
	type = rPROPERTY_TYPE_COLOR;
	value.colorVal = new rColor(c);
}

rProperty::rProperty(rFont* f){
	type = rPROPERTY_TYPE_FONT;
	value.fontVal = f;
}

rProperty::rProperty(rTexture2D* t){
	type = rPROPERTY_TYPE_TEXTURE;
	value.textureVal = t;
}

rProperty::~rProperty(){

	switch (type){
		case rPROPERTY_TYPE_STRING:
			delete value.stringVal;
			break;
		case rPROPERTY_TYPE_COLOR:
			delete value.colorVal;
			break;
	};
}
