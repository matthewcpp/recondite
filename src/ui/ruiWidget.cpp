#include "ui/ruiWidget.hpp"

ruiWidget::ruiWidget(const rString& id, rEngine* engine)
	:ruiWidgetBase(id, engine)
{
	m_position.Set(-1,-1);
	m_size.Set(-1,-1);

	BindDefaultEvents();
}

void ruiWidget::BindDefaultEvents(){
	Bind(ruiEVT_MOUSE_DOWN, this, &ruiWidget::OnMouseDown);
	Bind(ruiEVT_MOUSE_UP, this, &ruiWidget::OnMouseUp);
	Bind(ruiEVT_MOUSE_LEAVE, this, &ruiWidget::OnMouseLeave);
	Bind(ruiEVT_MOUSE_ENTER, this, &ruiWidget::OnMouseEnter);
}

ruiWidget::ruiWidget(const rString& id, rEngine* engine, const rPoint& position, const rSize& size)
	:ruiWidgetBase(id, engine)
{
	m_position = position;
	m_size = size;

	BindDefaultEvents();
}

rSize ruiWidget::Size() const{
	return m_size;
}

void ruiWidget::SetSize(int x, int y){
	m_size.Set(x, y);
}

rPoint ruiWidget::Position() const{
	return m_position;
}

void ruiWidget::SetPosition(int x, int y){
	m_position.Set(x, y);
}

rRect ruiWidget::BoundingBox() const{
	return rRect(m_position, m_size);
}

void ruiWidget::OnMouseDown(rEvent& event){
	ruiMouseEvent& mouseEvent = static_cast<ruiMouseEvent&>(event);

	if (mouseEvent.Button() == rMOUSE_BUTTON_LEFT)
		OnPointerDown(mouseEvent.Position());
}

void ruiWidget::OnMouseUp(rEvent& event){
	ruiMouseEvent& mouseEvent = static_cast<ruiMouseEvent&>(event);

	if (mouseEvent.Button() == rMOUSE_BUTTON_LEFT)
		OnPointerUp(mouseEvent.Position());
}

void ruiWidget::OnMouseLeave(rEvent& event){
	ruiMouseEvent& mouseEvent = static_cast<ruiMouseEvent&>(event);

	OnPointerLeave(mouseEvent.Position());
}

void ruiWidget::OnMouseEnter(rEvent& event){
	ruiMouseEvent& mouseEvent = static_cast<ruiMouseEvent&>(event);
	OnPointerEnter(mouseEvent.Position());
}