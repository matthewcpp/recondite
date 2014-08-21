#include "ui/ruiWidget.hpp"

ruiWidget::ruiWidget(const rString& id, rEngine* engine)
	:ruiStyledWidgetBase(id, engine)
{
	m_position.Set(-1,-1);
	m_size.Set(-1,-1);
}

ruiWidget::ruiWidget(const rString& id, rEngine* engine, const rPoint& position, const rSize& size)
	:ruiStyledWidgetBase(id, engine)
{
	m_position = position;
	m_size = size;
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

void ruiWidget::Trigger(int eventType){
	std::pair<ruiFunctorMap::iterator, ruiFunctorMap::iterator> result = m_eventTable.equal_range(eventType);

	for (ruiFunctorMap::iterator it = result.first; it != result.second; ++it)
		it->second->Call(this);
}
void ruiWidget::InsertEventBinding(int eventType, ruiWidgetFunctor* functor){
	m_eventTable.insert(std::make_pair(eventType , functor));
}


void ruiWidget::ShowModal(ruiWidget* widget){

}

void ruiWidget::EndModal(ruiWidget* widget){

}

void ruiWidget::OnTouchDown(const rTouch& touch){
	OnPointerDown(touch.GetCurrentPosition());
}

void ruiWidget::OnTouchMove(const rTouch& touch){
	OnPointerMove(touch.GetCurrentPosition());
}

void ruiWidget::OnTouchUp(const rTouch& touch){
	OnPointerUp(touch.GetCurrentPosition());
}

void ruiWidget::OnMouseLeftDown(const rMouseState& mouse){
	OnPointerDown(mouse.Position());
}

void ruiWidget::OnMouseLeftUp(const rMouseState& mouse){
	OnPointerUp(mouse.Position());
}

void ruiWidget::OnMouseMotion(const rMouseState& mouse){
	OnPointerMove(mouse.Position());
}