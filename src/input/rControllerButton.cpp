#include "input/rControllerButton.hpp"

rControllerButton::rControllerButton(){
	m_currentState = rBUTTON_STATE_UP;
	m_previousState = rBUTTON_STATE_UP;
}

void rControllerButton::SetButtonState(rButtonState state){
	m_previousState = m_currentState;
	m_currentState = state;
}

rButtonState rControllerButton::State() const{
	return m_currentState;
}

bool rControllerButton::Down() const{
	return m_currentState == rBUTTON_STATE_DOWN;
}

bool rControllerButton::Up() const{
	return m_currentState == rBUTTON_STATE_UP;
}

bool rControllerButton::Pressed() const{
	return m_currentState == rBUTTON_STATE_DOWN && m_previousState == rBUTTON_STATE_UP;
}

bool rControllerButton::Held() const{
	return m_currentState == rBUTTON_STATE_DOWN && m_previousState == rBUTTON_STATE_DOWN;
}

bool rControllerButton::Released() const{
	return m_currentState == rBUTTON_STATE_UP && m_previousState == rBUTTON_STATE_DOWN;
}
	