#ifndef R_INPUT_HPP
#define R_INPUT_HPP

#include <vector>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "input/rTouch.hpp"
#include "input/rDPad.hpp"
#include "input/rInputButton.hpp"
#include "input/rMouse.hpp"

#include "rVector2.hpp"

typedef std::vector<rInputButton> rButtonArray;
typedef std::vector<rDPad> rDPadArray;
typedef std::vector<rTouch*> rTouchArray;

class rControllerState{
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

class rInput {
public:
	virtual void GetTouches(rTouchArray& touches) const = 0;
	virtual rTouch* GetTouch(int id) = 0;

	virtual size_t ControllerCount() const = 0;
	virtual rControllerState* GetControllerState(size_t index) const = 0;
	virtual const rMouseState* GetMouseState() const = 0;
};

class rInputListener{
public:
	virtual void OnTouchEvent(const rTouch& touch) {}
};

#endif
