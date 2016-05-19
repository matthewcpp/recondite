#include "ui/ruiButton.hpp"

ruiButton::ruiButton(const rString& text, const rString& id, ruiDocument* document, rEngine* engine)
	:ruiWidget(id, document, engine)
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
	rRect boundingBox = BoundingBox();
	rColor color = rColor::White;

	RenderWidgetBase(style, boundingBox);
	
	Font::Face* font = DetermineFont();
	
	if (font){
		style->GetColor("color", color);
		m_engine->renderer->SpriteBatch()->RenderString(m_text, font, ContentPosition(), color, 0.01);
	}
	
}

rSize ruiButton::ComputeSize(){
	ruiStyle* style = ComputedStyle();
	Font::Face* font = DetermineFont();

	if (font)
		return font->MeasureString(m_text);
	else
		return rSize(0, 0);
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