#include "ui/ruiStyle.hpp"

ruiStyle::ruiStyle(){
	m_changed = false;
}

void ruiStyle::SetBool(const rString& key, bool val){
	rPropertyCollection::SetBool(key, val);
	m_changed = true;
}

void ruiStyle::SetFont(const rString& key, rFont* font){
	rPropertyCollection::SetFont(key, font);
	m_changed = true;
}

void ruiStyle::SetTexture(const rString& key, rTexture* texture){
	rPropertyCollection::SetTexture(key, texture);
	m_changed = true;
}

void ruiStyle::SetInt(const rString& key, int i){
	rPropertyCollection::SetInt(key, i);
	m_changed = true;
}

void ruiStyle::SetFloat(const rString& key, float f){
	rPropertyCollection::SetFloat(key, f);
	m_changed = true;
}

void ruiStyle::SetColor(const rString& key, const rColor& color){
	rPropertyCollection::SetColor(key, color);
	m_changed = true;
}

void ruiStyle::Extend(const ruiStyle& style){
	rPropertyMap::const_iterator end = style.m_properties.end();

	for (rPropertyMap::const_iterator it = style.m_properties.begin(); it != end; ++it){
		rProperty* p = it->second;

		switch (p->type){
		case rPROPERTY_TYPE_BOOL:
			SetBool(it->first, p->value.boolVal);
			break;

		case rPROPERTY_TYPE_INT:
			SetInt(it->first, p->value.intVal);
			break;

		case rPROPERTY_TYPE_FLOAT:
			SetFloat(it->first, p->value.floatVal);
			break;

		case rPROPERTY_TYPE_STRING:
			SetString(it->first, *(p->value.stringVal));
			break;

		case rPROPERTY_TYPE_COLOR:
			SetColor(it->first, *(p->value.colorVal));
			break;

		case rPROPERTY_TYPE_FONT:
			SetFont(it->first, p->value.fontVal);
			break;

		case rPROPERTY_TYPE_TEXTURE:
			SetTexture(it->first, p->value.textureVal);
			break;
		};
	}
}

bool ruiStyle::HasChanged() const{
	return m_changed;
}

void ruiStyle::MarkChanged(){
	m_changed = true;
}

void ruiStyle::ClearChanged(){
	m_changed = false;
}