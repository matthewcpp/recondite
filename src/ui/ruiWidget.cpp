#include "ui/ruiWidget.hpp"

ruiWidget::ruiWidget(const rString& id, rEngine* engine)
	:ruiWidgetBase(id, engine)
{
	m_position.Set(-1,-1);
}

ruiWidget::ruiWidget(const rString& id, rEngine* engine, const rPoint& position)
	:ruiWidgetBase(id, engine)
{
	m_position = position;
}


rPoint ruiWidget::Position() const{
	return m_position;
}

void ruiWidget::SetPosition(int x, int y){
	m_position.Set(x, y);
}

rRect ruiWidget::BoundingBox() const{
	return rRect(m_position, Size());
}