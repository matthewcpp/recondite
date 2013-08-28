#include "input/rTouch.hpp"

rTouch::rTouch(unsigned int id, const rPoint& pos, rTouchType type){
	m_id = id;
	Update(pos, type);
}

rTouch::rTouch(unsigned int id, int posX, int posY, rTouchType type){
	m_id = id;
	Update(posX, posY, type);
}

unsigned int rTouch::Id() const{
	return m_id;
}

void rTouch::Update(const rPoint& pos, rTouchType type){
	m_type = type;
	
	if (type == rTOUCH_DOWN){
		m_startPosition = pos;
	}
	
	m_currentPosition = pos;
}

void rTouch::Update(int posX, int posY, rTouchType type){
	rPoint p(posX, posY);
	Update(p, type);
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
