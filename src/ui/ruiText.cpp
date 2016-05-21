#include "ui/ruiText.hpp"

ruiText::ruiText(const rString& id, ruiIDocument* document, rEngine* engine)
	:ruiWidget(id, document, engine)
{
}
ruiText::ruiText(const rString& text, const rString& id, ruiIDocument* document, rEngine* engine)
	: ruiWidget(id, document, engine)
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

	RenderWidgetBase(style, boundingBox);

	Font::Face* font = DetermineFont();
	
	if (font){
		color.Set(255,255,255,255);
		style->GetColor("color", color);

		m_engine->renderer->SpriteBatch()->RenderString(m_text, font, ContentPosition(), color, 0.01);
	}
}

rString ruiText::GetWidgetType() const{
	return "text";
}

rSize ruiText::ComputeSize(){
	ruiStyle* style = ComputedStyle();
	Font::Face* font = DetermineFont();

	return font->MeasureString(m_text);
}