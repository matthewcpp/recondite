#ifndef R_DPAD_HPP
#define R_DPAD_HPP

#include "input/rInputButton.hpp"

enum rDPadButton{
	rDPAD_LEFT,
	rDPAD_RIGHT,
	rDPAD_UP,
	rDPAD_DOWN
};

class rDPad {
public:
	rInputButton& Left();
	rInputButton& Right();
	rInputButton& Up();
	rInputButton& Down();
	
	rInputButton& GetButton(rDPadButton button);
	void SetButtonState(rDPadButton button, rButtonState state);
private:
	
	rInputButton m_buttons[4];
};

#endif