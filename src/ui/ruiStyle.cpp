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

void ruiStyle::SetTexture(const rString& key, rTexture2D* texture){
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