#include "ui/ruiText.hpp"

ruiText::ruiText(const rString& id, ruiIManager* ui, rEngine* engine)
:ruiWidget(id, ui, engine)
{
}
ruiText::ruiText(const rString& text, const rString& id, ruiIManager* ui, rEngine* engine)
:ruiWidget(id, ui, engine)
{
	SetText(text);
}

rString ruiText::GetText() const{
	return m_text;
}

void ruiText::SetText(const rString& text){
	m_text = text;
	
	InvalidateSize();
}

void ruiText::Draw(){
	ruiStyle* style = ComputedStyle();

	rColor color(255,255,255,255);
	rRect boundingBox = BoundingBox();

	if (style->GetColor("background-color", color))
		m_engine->renderer->RenderRect(boundingBox, color);

	rFont* font = DetermineFont();
	
	if (font){
		color.Set(255,255,255,255);
		style->GetColor("color", color);

		m_engine->renderer->RenderString(m_text, font, boundingBox, color);
	}
}

rString ruiText::GetWidgetType() const{
	return "text";
}

rSize ruiText::ComputeSize(){
	ruiStyle* style = ComputedStyle();
	rFont* font = DetermineFont();

	if (font)
		return font->MeasureString(m_text);
	else
		return rSize(0,0);
}