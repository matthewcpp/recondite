#include "input/rDpad.hpp"

rControllerButton& rDPad::Left(){
	return GetButton(rDPAD_LEFT);
}

rControllerButton& rDPad::Right(){
	return GetButton(rDPAD_RIGHT);
}

rControllerButton& rDPad::Up(){
	return GetButton(rDPAD_UP);
}

rControllerButton& rDPad::Down(){
	return GetButton(rDPAD_DOWN);
}

rControllerButton& rDPad::GetButton(rDPadButton button){
	return m_buttons[button];
}

void rDPad::SetButtonState(rDPadButton button, rButtonState state){
	m_buttons[button].SetButtonState(state);
}
