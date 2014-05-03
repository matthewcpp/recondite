#ifndef R_INPUTBUTTON_HPP
#define R_INPUTBUTTON_HPP

#include "rBuild.hpp"
#include "rDefs.hpp"

class RECONDITE_API rInputButton {
public:
	rInputButton();
	
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
