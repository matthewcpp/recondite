#include "input/rDPad.hpp"

rInputButton& rDPad::Left(){
	return GetButton(rDPAD_LEFT);
}

rInputButton& rDPad::Right(){
	return GetButton(rDPAD_RIGHT);
}

rInputButton& rDPad::Up(){
	return GetButton(rDPAD_UP);
}

rInputButton& rDPad::Down(){
	return GetButton(rDPAD_DOWN);
}

rInputButton& rDPad::GetButton(rDPadButton button){
	return m_buttons[button];
}

void rDPad::SetButtonState(rDPadButton button, rButtonState state){
	m_buttons[button].SetButtonState(state);
}
