#include "input/rDragGesture.hpp"

rDragGesture::rDragGesture(){
	m_touchId = -1;
}

rString rDragGesture::Name() const{
	return "drag";
}

bool rDragGesture::Active() const{
	return m_touchId != -1;
}

float rDragGesture::Amount() const{
	if (Active())
		return m_position.Distance(m_prevPosition);
	else{
		return 0.0f;
	}
}

float rDragGesture::PreviousAmount() const{
	if (Active())
		return m_prevPosition.Distance(m_startPosition);
	else{
		return 0.0f;
	}
}

bool rDragGesture::Position(size_t index, rPoint& position) const{
	if (index == 0){
		position = m_position;
		return true;
	}
	else{
		return false;
	}
}

bool rDragGesture::PreviousPosition(size_t index, rPoint& position) const{
	if (index == 0){
		position = m_prevPosition;
		return true;
	}
	else{
		return false;
	}
}

void rDragGesture::OnTouchDown(const rTouch& touch){
	if (m_touchId == -1){
		m_touchId = touch.Id();
		m_startPosition = touch.GetCurrentPosition();
		m_prevPosition = m_startPosition;
		m_position = m_startPosition;
	}
}

void rDragGesture::OnTouchMove(const rTouch& touch){
	if (m_touchId == touch.Id()){
		m_prevPosition = m_position;
		m_position = touch.GetCurrentPosition();
	}
}

void rDragGesture::OnTouchUp(const rTouch& touch){
	if (m_touchId == touch.Id())
		m_touchId = -1;
}