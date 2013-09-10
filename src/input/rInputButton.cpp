#include "input/rInputButton.hpp"

rInputButton::rInputButton(){
	m_currentState = rBUTTON_STATE_UP;
	m_previousState = rBUTTON_STATE_UP;
}

void rInputButton::SetButtonState(rButtonState state){
	m_previousState = m_currentState;
	m_currentState = state;
}

rButtonState rInputButton::State() const{
	return m_currentState;
}

bool rInputButton::Down() const{
	return m_currentState == rBUTTON_STATE_DOWN;
}

bool rInputButton::Up() const{
	return m_currentState == rBUTTON_STATE_UP;
}

bool rInputButton::Pressed() const{
	return m_currentState == rBUTTON_STATE_DOWN && m_previousState == rBUTTON_STATE_UP;
}

bool rInputButton::Held() const{
	return m_currentState == rBUTTON_STATE_DOWN && m_previousState == rBUTTON_STATE_DOWN;
}

bool rInputButton::Released() const{
	return m_currentState == rBUTTON_STATE_UP && m_previousState == rBUTTON_STATE_DOWN;
}
	