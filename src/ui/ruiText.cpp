#include "ui/ruiText.hpp"

ruiText::ruiText(const rString& id, ruiIOverlay* overlay, rEngine* engine, const rPoint& position, const rSize& size)
:ruiWidget(id, overlay, engine, position, size)
{
}
ruiText::ruiText(const rString& text, const rString& id, ruiIOverlay* overlay, rEngine* engine, const rPoint& position, const rSize& size)
:ruiWidget(id, overlay, engine, position, size)
{
	SetText(text);
}

rString ruiText::GetText() const{
	return m_text;
}

void ruiText::SetText(const rString& text){
	m_text = text;
	
	m_cachedSize = rSize::Default;
}

void ruiText::Draw(rEngine& engine){
	rFont* font = engine.content->GetFontAsset("consolas");
	rColor red(255,0,0,255);
	rRect boundingBox = BoundingBox();

	engine.renderer->RenderRect(boundingBox, red);
	
	if (font){
		if (m_cachedSize == rSize::Default){
			m_cachedSize = font->MeasureString(m_text, m_size.x);
		}
		
		rColor white(255,255,255,255);
		engine.renderer->RenderString(m_text, font, boundingBox, white);
	}
}
