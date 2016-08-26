#include "ui/ruiWidget.hpp"
#include "ui/ruiDocument.hpp"

ruiWidget::ruiWidget(const rString& id, ruiIDocument* document, rEngine* engine)
	:rObject(id, engine)
{
	m_document = document;

	m_style.MarkChanged();
	InvalidateSize();
}

void ruiWidget::AddClass(const rString& className){
	if (!HasClass(className)){
		m_classList.push_back(className);
		m_style.MarkChanged();
		InvalidateSize();
	}
}

void ruiWidget::RemoveClass(const rString& className){
	int index = GetClassIndex(className);

	if (index >= 0){
		m_classList.erase(m_classList.begin() + index);
		m_style.MarkChanged();
		InvalidateSize();
	}
}

bool ruiWidget::HasClass(const rString& className) const{
	return GetClassIndex(className) >= 0;
}

void ruiWidget::GetClasses(rArrayString& classlist){
	classlist = m_classList;
}

void ruiWidget::ExtendStyle(const rString& selector){
	ruiStyle* style = m_document->Styles()->GetStyle(selector);
	if (style) m_computedStyle.Extend(*style);
}

void ruiWidget::RecomputeStyle(){
	m_computedStyle.Clear();

	ruiStyleManager* styleManager = m_document->Styles();
	ruiStyle* style = NULL;

	ExtendStyle(GetWidgetType());


	//next apply styles for each class assigned to this widget
	for (size_t i = 0; i < m_classList.size(); i++){
		ExtendStyle("." + m_classList[i]);
	}

	//apply a style for this particualr widget instance
	ExtendStyle("#" + Id());

	if (m_uiState.length() > 0) {
		ExtendStyle(GetWidgetType() + ":" + m_uiState);
		for (size_t i = 0; i < m_classList.size(); i++) {
			ExtendStyle("." + m_classList[i] + ":" + m_uiState);
		}
		ExtendStyle("#" + Id() + ":" + m_uiState);
	}

	//apply local style override
	m_computedStyle.Extend(m_style);

	m_style.ClearChanged();
	InvalidateSize();
}
void ruiWidget::Draw(){}

void ruiWidget::RenderWidgetBase(ruiStyle* style, const rRect& boundingBox){
	rColor color(255, 255, 255, 255);

	int borderRadius = 0;
	style->GetInt("border-radius", borderRadius);

	if (style->GetColor("background-color", color)){
		if (borderRadius > 0)
			m_engine->renderer->SpriteBatch()->RenderRoundedRectangle(boundingBox, borderRadius, color);
		else
			m_engine->renderer->SpriteBatch()->RenderRectangle(boundingBox, color);
	}

	if (style->GetColor("border-color", color)){
		if (borderRadius > 0)
			m_engine->renderer->SpriteBatch()->RenderWireRoundedRectangle(boundingBox, borderRadius, color, 0.01);
		else
			m_engine->renderer->SpriteBatch()->RenderWireRectangle(boundingBox, color, 0.01);
	}
}


void ruiWidget::Update(){
	if (m_style.HasChanged())
		RecomputeStyle();

	if (m_size == rSize::Default)
		RecomputeSize();

}

int ruiWidget::GetClassIndex(const rString& className) const{
	for (size_t i = 0; i < m_classList.size(); i++){
		if (m_classList[i] == className)
			return i;
	}

	return -1;
}

ruiStyle* ruiWidget::Style(){
	return &m_style;
}

ruiStyle* ruiWidget::ComputedStyle(){
	if (m_style.HasChanged())
		RecomputeStyle();

	return &m_computedStyle;
}

void ruiWidget::RecomputeSize(bool force){
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

rSize ruiWidget::Size(){
	RecomputeSize();
	return m_size;
}

rPoint ruiWidget::ContentOffset(){
	RecomputeSize();
	return m_contentOffset;
}

void ruiWidget::InvalidateSize(){
	m_size = rSize::Default;
	m_document->WidgetUpdated(this);
}

Font::Face* ruiWidget::DetermineFont(){
	ruiStyle* style = ComputedStyle();

	return m_engine->content->Fonts()->SystemDefault();
}

rString ruiWidget::UiState() const{
	return m_uiState;
}

void ruiWidget::UiState(const rString& state){
	if (state != m_uiState){
		m_uiState = state;
		m_style.MarkChanged();
	}
}

rRect ruiWidget::BoundingBox(){
	return rRect(m_position, Size());
}

rPoint ruiWidget::Position() const{
	return m_position;
}

void ruiWidget::SetPosition(const rPoint& position){
	m_position = position;
}

rPoint ruiWidget::ContentPosition(){
	return m_position + ContentOffset();
}

rPropertyCollection& ruiWidget::Properties() {
	return m_properties;
}