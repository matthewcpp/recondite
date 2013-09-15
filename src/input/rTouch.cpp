#include "input/rTouch.hpp"

rTouch::rTouch(int id, const rPoint& pos, rTouchType type){
	m_id = id;
	Update(pos, type);
}

rTouch::rTouch(int id, int posX, int posY, rTouchType type){
	m_id = id;
	Update(posX, posY, type);
}

int rTouch::Id() const{
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

rVector2 rTouch::GetCurrentPositionVector() const{
	return rVector2(m_currentPosition.x, m_currentPosition.y);
}

rTouchType rTouch::GetType() const{
	return m_type;
}
