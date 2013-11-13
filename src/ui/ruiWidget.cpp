#include "ui/ruiWidget.hpp"

ruiWidget::ruiWidget(int id){
	m_id = id;
	m_position.Set(-1,-1);
	m_size.Set(-1,-1);
}

ruiWidget::ruiWidget(int id, const rPoint& position, const rSize& size){
	m_id = id;
	m_position = position;
	m_size = size;
}

int ruiWidget::Id() const{
	return m_id;
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

ruiIWidgetManager* ruiWidget::widgetManager = NULL;

void ruiWidget::ShowModal(ruiWidget* widget){
	if (widgetManager)
		widgetManager->ShowModal(widget);
}

void ruiWidget::EndModal(ruiWidget* widget){
	if (widgetManager)
		widgetManager->EndModal(widget);
}
