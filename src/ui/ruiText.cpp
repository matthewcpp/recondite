#include "ui/ruiText.hpp"

ruiText::ruiText(const rString& id, ruiOverlay* overlay, rEngine* engine)
	:ruiWidget(id, overlay, engine)
{
}
ruiText::ruiText(const rString& text, const rString& id, ruiOverlay* overlay, rEngine* engine)
	: ruiWidget(id, overlay, engine)
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

	Font::Face* font = DetermineFont();
	
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
	Font::Face* font = DetermineFont();

	if (font)
		return font->MeasureString(m_text);
	else
		return rSize(0,0);
}