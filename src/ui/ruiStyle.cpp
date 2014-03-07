#include "ui/ruiStyle.hpp"

bool ruiStyle::GetFont(const rString& name, rFont** font) const{
	ruiStylePropertyMap::const_iterator p = m_properties.find(name);

	if (p != m_properties.end()){
		*font = p->second.m_font;
		return true;
	}
	else{
		return false;
	};
}

void ruiStyle::SetFont(const rString& name, rFont* font){
	m_properties[name].m_font = font;
}


bool ruiStyle::GetTexture(const rString& name, rTexture2D** texture) const{
	ruiStylePropertyMap::const_iterator p = m_properties.find(name);

	if (p != m_properties.end()){
		*texture = p->second.m_texture;
		return true;
	}
	else{
		return false;
	}
}

void ruiStyle::SetTexture(const rString& name, rTexture2D* texture){
	m_properties[name].m_texture = texture;
}

bool ruiStyle::GetInt(const rString& name, int& i) const{
	ruiStylePropertyMap::const_iterator p = m_properties.find(name);

	if (p != m_properties.end()){
		i = p->second.m_int;
		return true;
	}
	else{
		return false;
	}
}

void ruiStyle::SetInt(const rString& name, int i){
	m_properties[name].m_int = i;
}

bool ruiStyle::GetFloat(const rString& name, float& f) const{
	ruiStylePropertyMap::const_iterator p = m_properties.find(name);

	if (p != m_properties.end()){
		f = p->second.m_float;
		return true;
	}
	else{
		return false;
	}
}

void ruiStyle::SetFloat(const rString& name, float f){
	m_properties[name].m_float = f;
}

bool ruiStyle::GetColor(const rString& name, rColor& color) const{
	ruiStylePropertyMap::const_iterator p = m_properties.find(name);

	if (p != m_properties.end()){
		color.Set(p->second.m_color);
		return true;
	}
	else{
		return false;
	};
}

void ruiStyle::SetColor(const rString& name, const rColor& color){
	color.ToArray(m_properties[name].m_color);
}

void ruiStyle::Extend(const ruiStyle& style){
}