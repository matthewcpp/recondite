#ifndef R_DPAD_HPP
#define R_DPAD_HPP

#include "input/rControllerButton.hpp"

enum rDPadButton{
	rDPAD_LEFT,
	rDPAD_RIGHT,
	rDPAD_UP,
	rDPAD_DOWN
};

class rDPad {
public:
	rControllerButton& Left();
	rControllerButton& Right();
	rControllerButton& Up();
	rControllerButton& Down();
	
	rControllerButton& GetButton(rDPadButton button);
	void SetButtonState(rDPadButton button, rButtonState state);
private:
	
	rControllerButton m_buttons[4];
};

#endif