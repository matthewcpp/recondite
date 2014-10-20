#include "ui/ruiButton.hpp"

ruiButton::ruiButton(const rString& text, const rString& id, rEngine* engine)
	:ruiWidget(id, engine)
{
	m_text = text;
	m_state = rBUTTON_STATE_UP;
}


rString ruiButton::GetText() const{
	return m_text;
}

void ruiButton::SetText(const rString& text){
	m_text = text;

	InvalidateSize();
}

void ruiButton::Draw(rEngine& engine){
	ruiStyle* style = ComputedStyle();
	rRect box = BoundingBox();
	
	rColor color;

	switch (m_state){
		case rBUTTON_STATE_DOWN:
			color.Set(150,150,150,255);
			break;
		case rBUTTON_STATE_UP:
			color.Set(200,200,200,255);
			break;

		case rBUTTON_STATE_NONE:
			color.Set(175,175,175,255);
			break;
	};
	
	engine.renderer->RenderRoundedRect(box, 10, color);
	
	rFont* font = DetermineFont();
	
	if (font){
		rPoint center = box.Center();
		rPoint textPos(center.x - (box.width / 2), center.y - (box.height / 2));
		
		engine.renderer->RenderString(m_text, font, textPos, rColor::Black);
	}
	
}

rSize ruiButton::ComputeSize(){
	ruiStyle* style = ComputedStyle();

	rFont* font = DetermineFont();

	if (font)
		return font->MeasureString(m_text);
	else
		return rSize(0,0);
}

bool ruiButton::OnPointerDown(const rPoint& position){
	m_state = rBUTTON_STATE_DOWN;
	return true;
}

bool ruiButton::OnPointerUp(const rPoint& position){
	m_state = rBUTTON_STATE_UP;

	rRect box = BoundingBox();

	if (box.ContainsPoint(position)){
		ruiWidgetEvent event(this);
		Trigger(ruiEVENT_BUTTON_CLICK, event);
	}

	return true;
}

bool ruiButton::OnPointerLeave(const rPoint& position){
	if (m_state == rBUTTON_STATE_DOWN)
		m_state = rBUTTON_STATE_NONE;
	else
		m_state = rBUTTON_STATE_UP;

	return true;
}

bool ruiButton::OnPointerEnter(const rPoint& position){
	if (m_state == rBUTTON_STATE_NONE)
		m_state = rBUTTON_STATE_DOWN;

	return true;
}

rButtonState ruiButton::ButtonState() const{
	return m_state;
}

rString ruiButton::GetWidgetType() const{
	return "button";
}