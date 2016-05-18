#include "ui/ruiWidgetBase.hpp"
#include "ui/ruiOverlay.hpp"

ruiWidgetBase::ruiWidgetBase(const rString& id, ruiOverlay* ui, rEngine* engine)
	:rObject(id, engine)
{
	m_overlay = ui;

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
	ruiStyle* style = m_overlay->Styles()->GetStyle(selector);
	if (style) m_computedStyle.Extend(*style);
}

void ruiWidgetBase::RecomputeStyle(){
	m_computedStyle.Clear();

	ruiStyleManager* styleManager = m_overlay->Styles();
	ruiStyle* style = NULL;

	ExtendStyle(GetWidgetType());
	

	//next apply styles for each class assigned to this widget
	for (size_t i = 0; i < m_classList.size(); i++){
		ExtendStyle("." + m_classList[i]);
		ExtendStyle("." + m_classList[i] + ":" + m_uiState);
	}

	//apply a style for this particualr widget instance
	ExtendStyle("#" + Id());
	

	//apply local style override
	m_computedStyle.Extend(m_style);

	ExtendStyle(GetWidgetType() + ":" + m_uiState);
	for (size_t i = 0; i < m_classList.size(); i++){
		ExtendStyle("." + m_classList[i] + ":" + m_uiState);
	}
	ExtendStyle("#" + Id() + ":" + m_uiState);

	m_style.ClearChanged();
	RecomputeSize(true);
}
void ruiWidgetBase::Draw(){}


void ruiWidgetBase::Update(){
	if (m_style.HasChanged())
		RecomputeStyle();

	if (m_size == rSize::Default)
		m_size = ComputeSize();

}

int ruiWidgetBase::GetClassIndex(const rString& className) const{
	for (size_t i = 0; i < m_classList.size(); i++){
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

void ruiWidgetBase::RecomputeSize(bool force){
	if (force || m_size == rSize::Default){
		m_size = ComputeSize();
		ruiStyle* style = ComputedStyle();
		m_contentOffset.Set(0, 0);

		int padding[4] = { 0, 0, 0, 0 };
		style->GetInt("padding-top", padding[0]);
		style->GetInt("padding-right", padding[1]);
		style->GetInt("padding-bottom", padding[2]);
		style->GetInt("padding-left", padding[3]);

		m_size.x += padding[1] + padding[3];
		m_size.y += padding[0] + padding[2];

		m_contentOffset.x += padding[3];
		m_contentOffset.y += padding[0];

		if (style->HasKey("border-color")){
			m_size.x += 2;
			m_size.y += 2;

			m_contentOffset.x += 1;
			m_contentOffset.x += 1;
		}
	}
}

rSize ruiWidgetBase::Size(){
	RecomputeSize();
	return m_size;
}

rPoint ruiWidgetBase::ContentOffset(){
	RecomputeSize();
	return m_contentOffset;
}

void ruiWidgetBase::InvalidateSize(){
	m_size = rSize::Default;
}

Font::Face* ruiWidgetBase::DetermineFont(){
	ruiStyle* style = ComputedStyle();

	return m_engine->content->Fonts()->SystemDefault();
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