#include "ui/ruiWidget.hpp"

ruiWidget::ruiWidget(const rString& id, ruiIDocument* document, rEngine* engine)
	:ruiWidgetBase(id, document, engine)
{
	m_position.Set(-1,-1);
	m_position.Set(0,0);
}


rPoint ruiWidget::Position() const{
	return m_position;
}

void ruiWidget::SetPosition(int x, int y){
	m_position.Set(x, y);
}

void ruiWidget::SetPosition(const rPoint& position){
	m_position = position;
}

rRect ruiWidget::BoundingBox(){
	return rRect(m_position, Size());
}

rPoint ruiWidget::ContentPosition(){
	return m_position + ContentOffset();
}