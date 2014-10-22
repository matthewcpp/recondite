#include "ui/ruiWidgetBase.hpp"

ruiWidgetBase::ruiWidgetBase(const rString& id, rEngine* engine)
	:rObject(id, engine)
{
	m_style.MarkChanged();
	InvalidateSize();
}

void ruiWidgetBase::AddClass(const rString& className){
	if (!HasClass(className)){
		m_classList.push_back(className);
		m_style.MarkChanged();
		InvalidateSize();
	}
}

void ruiWidgetBase::RemoveClass(const rString& className){
	int index = GetClassIndex(className);

	if (index >= 0){
		m_classList.erase(m_classList.begin() + index);
		m_style.MarkChanged();
		InvalidateSize();
	}
}

bool ruiWidgetBase::HasClass(const rString& className) const{
	return GetClassIndex(className) >= 0;
}

void ruiWidgetBase::GetClasses(rArrayString& classlist){
	classlist = m_classList;
}

void ruiWidgetBase::ExtendStyle(const rString& selector){
	ruiStyle* style = m_engine->ui->Styles()->GetStyle(selector);
	if (style) m_computedStyle.Extend(*style);
}

void ruiWidgetBase::RecomputeStyle(){
	m_computedStyle.Clear();
	ruiStyleManager* styleManager = m_engine->ui->Styles();
	ruiStyle* style = NULL;

	//start with any base level styles for this widget type
	ExtendStyle(GetWidgetType());
	ExtendStyle(GetWidgetType() + ":" + m_uiState);

	//next we apply stles for each class assigned to this widget
	for (size_t i = 0; i < m_classList.size(); i++){
		ExtendStyle("." + m_classList[i]);
		ExtendStyle("." + m_classList[i] + ":" + m_uiState);
	}

	//apply a style for this particualr widget instance
	ExtendStyle("#" + Id());
	ExtendStyle("#" + Id() + ":" + m_uiState);

	//finally apply local style override
	m_computedStyle.Extend(m_style);

	m_style.ClearChanged();
	InvalidateSize();
}
void ruiWidgetBase::Draw(rEngine& engine){}


void ruiWidgetBase::Update(rEngine& engine){
	if (m_style.HasChanged())
		RecomputeStyle();

	if (m_size == rSize::Default)
		m_size = ComputeSize();

}

int ruiWidgetBase::GetClassIndex(const rString& className) const{
	for (int i = 0; i < m_classList.size(); i++){
		if (m_classList[i] == className)
			return i;
	}

	return -1;
}

ruiStyle* ruiWidgetBase::Style(){
	return &m_style;
}

ruiStyle* ruiWidgetBase::ComputedStyle(){
	if (m_style.HasChanged())
		RecomputeStyle();

	return &m_computedStyle;
}

rSize ruiWidgetBase::Size(){
	if (m_size == rSize::Default)
		m_size = ComputeSize();

	return m_size;
}

void ruiWidgetBase::InvalidateSize(){
	m_size = rSize::Default;
}

rFont* ruiWidgetBase::DetermineFont(){
	ruiStyle* style = ComputedStyle();

	rString fontName = "consolas";
	style->GetString("font", fontName);
	return m_engine->content->GetFontAsset(fontName);
}

rString ruiWidgetBase::UiState() const{
	return m_uiState;
}

void ruiWidgetBase::UiState(const rString& state){
	if (state != m_uiState){
		m_uiState = state;
		m_style.MarkChanged();
	}
}