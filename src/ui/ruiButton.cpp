#include "ui/ruiButton.hpp"

ruiButton::ruiButton(const rString& text,const rString& id, rEngine* engine, const rPoint& position, const rSize& size)
:ruiWidget(id, engine, position, size)
{
	SetText(text);
	m_state = rBUTTON_STATE_UP;
}


rString ruiButton::GetText() const{
	return m_text;
}

void ruiButton::SetText(const rString& text){
	m_text = text;

	m_cachedSize = rSize::Default;
}

void ruiButton::Draw(rEngine& engine){
	rRect box = BoundingBox();
	
	
	rColor gray(200,200,200,255);
	rColor darkgray(150,150,150,255);
	
	if (m_state == rBUTTON_STATE_DOWN)
		engine.renderer->RenderRoundedRect(box, 10, darkgray);
	else
		engine.renderer->RenderRoundedRect(box, 10, gray);

	
	rFont* font = engine.content->GetFontAsset("consolas");
	
	if (font){
		if (m_cachedSize == rSize::Default){
			m_cachedSize = font->MeasureString(m_text, m_size.x);
		}

		rPoint center = box.Center();
		rPoint textPos(center.x - (m_cachedSize.x / 2), center.y - (m_cachedSize.y / 2));
		
		engine.renderer->RenderString(m_text, font, textPos, rColor::Black);
	}
	
}

void ruiButton::OnPointerDown(const rPoint& position){
	m_state = rBUTTON_STATE_DOWN;
}

void ruiButton::OnPointerUp(const rPoint& position){
	m_state = rBUTTON_STATE_UP;

	rRect box = BoundingBox();

	if (box.ContainsPoint(position)){
		Trigger(ruiEVENT_BUTTON_CLICK);
	}
}

rButtonState ruiButton::GetState() const{
	return m_state;
}
