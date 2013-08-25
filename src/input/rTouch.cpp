#include "rTouch.hpp"

rTouch::rTouch(unsigned int id, rTouchType type, const rPoint& pos){
	m_id = id;
	Update(type, pos);
}

rTouch::rTouch(unsigned int id, rTouchType type, int posX, int posY){
	m_id = id;
	Update(type, posX, posY);
}

unsigned int rTouch::Id() const{
	return m_id;
}

void rTouch::Update(rTouchType type, const rPoint& pos){
	m_type = type;
	
	if (type == rTOUCH_DOWN){
		m_startPosition = pos;
	}
	
	m_currentPosition = pos;
}

void rTouch::Update(rTouchType type, int posX, int posY){
	rPoint p(posX, posY);
	Update(type, p);
}

rPoint rTouch::GetStartPosition() const{
	return m_startPosition;
}

rPoint rTouch::GetCurrentPosition() const{
	return m_currentPosition;
}

rTouchType rTouch::GetType() const{
	return m_type;
}