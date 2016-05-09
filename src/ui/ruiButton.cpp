#include "ui/ruiButton.hpp"

ruiButton::ruiButton(const rString& text, const rString& id, ruiIManager* ui, rEngine* engine)
	:ruiWidget(id, ui, engine)
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

void ruiButton::Draw(){
	ruiStyle* style = ComputedStyle();
	int padding[4] = {5,5,5,5};
	style->GetInt("padding-top", padding[0]);
	style->GetInt("padding-right", padding[1]);

	rRect box = BoundingBox();
	
	rColor color(200,200,200,255);
	style->GetColor("background-color", color);

	int borderRadius = 10;
	style->GetInt("border-radius", borderRadius);

	if (borderRadius > 0)
		m_engine->renderer->RenderRoundedRect(box, borderRadius, color);
	else
		m_engine->renderer->RenderRect(box, color);
	
	Font::Face* font = DetermineFont();
	
	if (font){
		color = rColor::Black;
		style->GetColor("color", color);

		rPoint textPos(m_position.x + padding[1], m_position.y + padding[0]);
		m_engine->renderer->RenderString(m_text, font, textPos, color);
	}
	
}

rSize ruiButton::ComputeSize(){
	ruiStyle* style = ComputedStyle();

	int padding[4] = {5,5,5,5};
	style->GetInt("padding-top", padding[0]);
	style->GetInt("padding-right", padding[1]);
	style->GetInt("padding-bottom", padding[2]);
	style->GetInt("padding-left", padding[3]);

	Font::Face* font = DetermineFont();

	rSize widgetSize(padding[1] + padding[3], padding[0] + padding[2]);

	if (font){
		rSize fontSize = font->MeasureString(m_text);
		widgetSize.x += fontSize.x;
		widgetSize.y += fontSize.y;
	}

	return widgetSize;
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