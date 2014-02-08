#include "input/rPinchGesture.hpp"

rPinchGesture::rPinchGesture(){
	m_touch1Id = -1;
	m_touch2Id = -1;
}

rString rPinchGesture::Name() const{
	return "pinch";
}

bool rPinchGesture::Active() const{
	return (m_touch1Id >= 0 && m_touch2Id >= 0);
}

float rPinchGesture::Amount() const{
	if (Active())
		return touch1Pos.Distance(touch2Pos);
	else
		return 0.0f;
}

float rPinchGesture::PreviousAmount() const{
	if (Active())
		return touch1Prev.Distance(touch2Prev);
	else
		return 0.0f;
}

bool rPinchGesture::Position(size_t index, rPoint& position) const{
	if (!Active())
		return false;
	
	if (index == 0){
		position = touch1Pos;
		return true;
	}
	else if (index == 1){
		position = touch2Pos;
		return true;
	}
	else{
		return false;
	}
}

bool rPinchGesture::PreviousPosition(size_t index, rPoint& position) const{
	if (!Active())
		return false;
	
	if (index == 0){
		position = touch1Prev;
		return true;
	}
	else if (index == 1){
		position = touch2Prev;
		return true;
	}
	else{
		return false;
	}
}

void rPinchGesture::OnTouchDown(const rTouch& touch){
	if (m_touch1Id == -1){
		m_touch1Id = touch.Id();
		touch1Pos = touch.GetCurrentPosition();
		touch1Prev = touch1Pos;
	}
	else if (m_touch2Id == -1){
		m_touch2Id = touch.Id();
		touch2Pos = touch.GetCurrentPosition();
		touch2Prev = touch2Pos;
	}
}

void rPinchGesture::OnTouchMove(const rTouch& touch){
	int id = touch.Id();
	
	if (m_touch1Id == id){
		touch1Prev = touch1Pos;
		touch1Pos = touch.GetCurrentPosition();
	}
	else if (m_touch2Id == id){
		touch2Prev = touch2Pos;
		touch2Pos = touch.GetCurrentPosition();
	}
}

void rPinchGesture::OnTouchUp(const rTouch& touch){
	int id = touch.Id();
	
	if (m_touch1Id == id){
		m_touch1Id = -1;
	}
	
	if (m_touch2Id == id){
		m_touch2Id = -1;
	}
}