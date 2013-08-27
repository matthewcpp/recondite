#ifndef R_CONTROLLER_HPP
#define R_CONTROLLER_HPP

#include <vector>

#include "rTypes.hpp"
#include "rDefs.hpp"
#include "rVector2.hpp"

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

enum rDPadButton{
	rDPAD_LEFT,
	rDPAD_RIGHT,
	rDPAD_UP,
	rDPAD_DOWN
}

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
}

typedef std::vector<rButton> rButtonArray;
typedef std::vector<rDPad> rDPadArray;

class rController{
public:
	rController(unsigned int buttonCount, unsigned int dPadCount, unsigned int analogStickCount, unsigned int triggerCount);
	void Init(unsigned int buttonCount, unsigned int dPadCount, unsigned int analogStickCount, unsigned int triggerCount);
	
public:
	virtual unsigned int ButtonCount() const;
	virtual unsigned int DPadCount() const;
	virtual unsigned int AnalogStickCount() const;
	virtual unsigned int TriggerCount() const;
	
	virtual const rButton* Button(unsigned int index) const;
	virtual const rDpad* DPad(unsigned int index) const;
	virtual const rVector2* AnalogStick(unsigned int index) const;
	virtual float Trigger(unsigned int index) const;
	
	bool SetButton(unsigned int index, rButtonState state);
	bool SetDPadButton(unsigned int index, rDPadButton button, rButtonState state);
	bool SetAnalogStick(unsigned int index, float x, float y);
	bool SetTrigger(unsigned int index, float value);
	
private:
	rButtonArray m_buttons;
	rDPadArray m_dPads;
	rVector2Array m_analogSticks;
	rFloatArray m_triggers;
};

#endif
