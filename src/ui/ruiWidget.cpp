#include "ui/ruiWidget.hpp"

ruiWidget::ruiWidget(const rString& id, rEngine* engine)
	:ruiWidgetBase(id, engine)
{
	m_position.Set(-1,-1);
	m_size.Set(-1,-1);
}

ruiWidget::ruiWidget(const rString& id, rEngine* engine, const rPoint& position, const rSize& size)
	:ruiWidgetBase(id, engine)
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