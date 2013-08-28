#ifndef R_CONTROLLERBUTTON_HPP
#define R_CONTROLLERBUTTON_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

enum rButtonState {
	rBUTTON_STATE_UP,
	rBUTTON_STATE_DOWN
};

class rControllerButton {
public:
	rControllerButton();
	
public:
	
	void SetButtonState(rButtonState state);
	rButtonState State() const;
	
	bool Down() const;
	bool Up() const;
	bool Pressed() const;
	bool Held() const;
	bool Released() const;
	
private:
	rButtonState m_currentState;
	rButtonState m_previousState;
};

#endif