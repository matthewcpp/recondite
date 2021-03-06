#ifndef R_CONTROLLER_HPP
#define R_CONTROLLER_HPP

#include <vector>

#include "rBuild.hpp"

#include "rTypes.hpp"
#include "rDefs.hpp"
#include "rVector2.hpp"

#include "rInput.hpp"
#include "input/rInputButton.hpp"

class RECONDITE_API rController : public rControllerState{
public:
	rController(unsigned int buttonCount, unsigned int dPadCount, unsigned int analogStickCount, unsigned int triggerCount);
	void Init(unsigned int buttonCount, unsigned int dPadCount, unsigned int analogStickCount, unsigned int triggerCount);
	
public:
	virtual unsigned int ButtonCount() const;
	virtual unsigned int DPadCount() const;
	virtual unsigned int AnalogStickCount() const;
	virtual unsigned int TriggerCount() const;
	
	virtual const rInputButton* Button(unsigned int index) const;
	virtual const rDPad* DPad(unsigned int index) const;
	virtual const rVector2* AnalogStick(unsigned int index) const;
	virtual float Trigger(unsigned int index) const;
	
	rDPad* DPad(unsigned int index);
	rInputButton* Button(unsigned int index);
	
	bool SetButton(unsigned int index, rButtonState state);
	bool SetDPadButton(unsigned int index, rDPadButton button, rButtonState state);
	bool SetAnalogStick(unsigned int index, float x, float y);
	bool SetTrigger(unsigned int index, float value);

private:
	typedef std::vector<rInputButton> rButtonArray;
	typedef std::vector<rDPad> rDPadArray;
	
private:
	rButtonArray m_buttons;
	rDPadArray m_dPads;
	rVector2Array m_analogSticks;
	rFloatArray m_triggers;
};

#endif
