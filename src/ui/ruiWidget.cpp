#include "ui/ruiWidget.hpp"

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