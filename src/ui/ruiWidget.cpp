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

rPoint ruiWidget::Position() const{
	return m_position;
}

rRect ruiWidget::BoundingBox() const{
	return rRect(m_position, m_size);
}
