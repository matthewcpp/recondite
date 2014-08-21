#include "ui/ruiStyledWidgetBase.hpp"

ruiStyledWidgetBase::ruiStyledWidgetBase(const rString& id, rEngine* engine)
	:ruiWidgetBase(id, engine)
{}

void ruiStyledWidgetBase::AddClass(const rString& className){
	if (!HasClass(className))
		m_classList.push_back(className);
}

void ruiStyledWidgetBase::RemoveClass(const rString& className){
	int index = GetClassIndex(className);

	if (index >= 0)
		m_classList.erase(m_classList.begin() + index);
}

bool ruiStyledWidgetBase::HasClass(const rString& className) const{
	return GetClassIndex(className) >= 0;
}

void ruiStyledWidgetBase::GetClasses(rArrayString& classlist){
	classlist = m_classList;
}

void ruiStyledWidgetBase::RecomputeStyle(){
}

int ruiStyledWidgetBase::GetClassIndex(const rString& className) const{
	for (int i = 0; i < m_classList.size(); i++){
		if (m_classList[i] == className)
			return i;
	}

	return -1;
}

ruiStyle* ruiStyledWidgetBase::WidgetStyle(){
	return &m_style;
}