#ifndef R_INPUT_HPP
#define R_INPUT_HPP

#include <vector>

#include "rBuild.hpp"
#include "rDefs.hpp"

#include "input/rTouch.hpp"
#include "input/rDPad.hpp"
#include "input/rInputButton.hpp"
#include "input/rMouse.hpp"
#include "input/rKeyboard.hpp"
#include "input/riGesture.hpp"

#include "rVector2.hpp"



class RECONDITE_API rControllerState{
public:
	virtual unsigned int ButtonCount() const = 0;
	virtual unsigned int DPadCount() const = 0;
	virtual unsigned int AnalogStickCount() const = 0;
	virtual unsigned int TriggerCount() const = 0;
	
	virtual const rInputButton* Button(unsigned int index) const = 0;
	virtual const rDPad* DPad(unsigned int index) const = 0;
	virtual const rVector2* AnalogStick(unsigned int index) const = 0;
	virtual float Trigger(unsigned int index) const = 0;
};

class RECONDITE_API rInput {
public:
	virtual rTouch* GetTouch(int id) = 0;
	virtual size_t TouchCount() const = 0;

	virtual size_t ControllerCount() const = 0;
	virtual rControllerState* GetControllerState(size_t index) const = 0;
	virtual const rMouseState* GetMouseState() const = 0;

	virtual const rKeyboardState* Keyboard() const = 0;

	virtual const riGestureTracker* Gestures() const = 0;
};

#endif
