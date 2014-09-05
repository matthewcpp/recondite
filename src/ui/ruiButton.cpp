#include "ui/ruiButton.hpp"

ruiButton::ruiButton(const rString& text, const rString& id, rEngine* engine, const rPoint& position, const rSize& size)
:ruiWidget(id, engine, position, size)
{
	SetText(text);
	m_state = rBUTTON_STATE_UP;

	Bind(ruiEVT_MOUSE_DOWN, this, &ruiButton::OnMouseDown);
	Bind(ruiEVT_MOUSE_UP, this, &ruiButton::OnMouseUp);
	Bind(ruiEVT_MOUSE_LEAVE, this, &ruiButton::OnMouseLeave);
	Bind(ruiEVT_MOUSE_ENTER, this, &ruiButton::OnMouseEnter);
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
		//trigger button click
	}
}

void ruiButton::OnPointerLeave(const rPoint& position){
	if (m_state == rBUTTON_STATE_DOWN)
		m_state = rBUTTON_STATE_NONE;
	else
		m_state = rBUTTON_STATE_UP;
}

void ruiButton::OnPointerEnter(const rPoint& position){
	if (m_state == rBUTTON_STATE_NONE)
		m_state = rBUTTON_STATE_DOWN;
}

rButtonState ruiButton::ButtonState() const{
	return m_state;
}

void ruiButton::OnMouseDown(rEvent& event){
	ruiMouseEvent& mouseEvent = static_cast<ruiMouseEvent&>(event);

	if (mouseEvent.Button() == rMOUSE_BUTTON_LEFT)
		OnPointerDown(mouseEvent.Position());
}

void ruiButton::OnMouseUp(rEvent& event){
	ruiMouseEvent& mouseEvent = static_cast<ruiMouseEvent&>(event);

	if (mouseEvent.Button() == rMOUSE_BUTTON_LEFT)
		OnPointerUp(mouseEvent.Position());
}

void ruiButton::OnMouseLeave(rEvent& event){
	ruiMouseEvent& mouseEvent = static_cast<ruiMouseEvent&>(event);

	OnPointerLeave(mouseEvent.Position());
}

void ruiButton::OnMouseEnter(rEvent& event){
	ruiMouseEvent& mouseEvent = static_cast<ruiMouseEvent&>(event);
	OnPointerEnter(mouseEvent.Position());
}