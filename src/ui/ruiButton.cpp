#include "ui/ruiButton.hpp"

ruiButton::ruiButton(const rString& text,int id, const rPoint& position, const rSize& size)
:ruiWidget(id, position, size)
{
	m_text = text;
	m_state = rBUTTON_STATE_UP;
}


rString ruiButton::GetText() const{
	return m_text;
}

void ruiButton::SetText(const rString& text){
	m_text = text;
}

void ruiButton::Draw(rEngine& engine){
	rRect box = BoundingBox();
	
	
	rColor gray(200,200,200,255);
	rColor darkgray(150,150,150,255);
	rColor black(0,0,0,255);
	
	if (m_state == rBUTTON_STATE_DOWN)
		engine.renderer->RenderRect(box, darkgray);
	else
		engine.renderer->RenderRect(box, gray);
	
	rFont* font = engine.content->GetFontAsset("consolas");
	
	if (font){
		rPoint center = box.Center();
		rSize strSize = font->MeasureString(m_text);
		rPoint textPos(center.x - (strSize.x / 2), center.y - (strSize.y / 2));
		
		engine.renderer->RenderString(m_text, font, textPos, black);
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
