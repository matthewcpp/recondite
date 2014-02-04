#include "input/rMouse.hpp"

rMouse::rMouse(){
	m_previousPosition = rPoint::Zero;
	m_position = rPoint::Zero;
	m_wheelValue = 0;
}

void rMouse::SetPosition(const rPoint& position){
	m_previousPosition = m_position;
	m_position = position;
}

void rMouse::SetPosition(int x, int y){
	m_previousPosition = m_position;

	m_position.Set(x,y);
}

rPoint rMouse::Position() const{
	return m_position;
}

rPoint rMouse::PreviousPosition() const {
	return m_previousPosition;
}

rButtonState rMouse::GetButtonState(rMouseButton button) const{
	return m_buttons[button].State();
}

void rMouse::SetButtonState(rMouseButton button, rButtonState state){
	m_buttons[button].SetButtonState(state);
}

void rMouse::UpdateWheelValue(rMouseWheelDirection direction){
	if (direction == rMOUSEWHEEL_UP)
		m_wheelValue += 1;
	else
		m_wheelValue -= 1;

}

int rMouse::GetWheelValue() const{
	return m_wheelValue;
}