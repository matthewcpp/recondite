#include "ui/ruiWidgetBase.hpp"

ruiWidgetBase::ruiWidgetBase(const rString& id, rEngine* engine)
	:rObject(id, engine)
{}

void ruiWidgetBase::AddClass(const rString& className){
	if (!HasClass(className))
		m_classList.push_back(className);
}

void ruiWidgetBase::RemoveClass(const rString& className){
	int index = GetClassIndex(className);

	if (index >= 0)
		m_classList.erase(m_classList.begin() + index);
}

bool ruiWidgetBase::HasClass(const rString& className) const{
	return GetClassIndex(className) >= 0;
}

void ruiWidgetBase::GetClasses(rArrayString& classlist){
	classlist = m_classList;
}

void ruiWidgetBase::RecomputeStyle(){
}

void ruiWidgetBase::Update(rEngine& engine){
	if (m_style.HasChanged())
		RecomputeStyle();
}

int ruiWidgetBase::GetClassIndex(const rString& className) const{
	for (int i = 0; i < m_classList.size(); i++){
		if (m_classList[i] == className)
			return i;
	}

	return -1;
}

ruiStyle* ruiWidgetBase::WidgetStyle(){
	return &m_style;
}