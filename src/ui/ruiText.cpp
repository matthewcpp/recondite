#include "ui/ruiText.hpp"

ruiText::ruiText(const rString& id, rEngine* engine)
:ruiWidget(id, engine)
{
}
ruiText::ruiText(const rString& text, const rString& id, rEngine* engine)
:ruiWidget(id, engine)
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

void ruiText::Draw(rEngine& engine){
	rFont* font = engine.content->GetFontAsset("consolas");
	rColor red(255,0,0,255);
	rRect boundingBox = BoundingBox();

	engine.renderer->RenderRect(boundingBox, red);
	
	if (font){
		rColor white(255,255,255,255);
		engine.renderer->RenderString(m_text, font, boundingBox, white);
	}
}

rString ruiText::GetWidgetType() const{
	return "text";
}

rSize ruiText::ComputeSize() const{
	rFont* font = m_engine->content->GetFontAsset("consolas");

	if (font)
		return font->MeasureString(m_text);
	else
		return rSize(0,0);
}