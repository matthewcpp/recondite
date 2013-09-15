#ifndef R_INPUTMANAGER_HPP
#define R_INPUTMANAGER_HPP

#include <map>
#include <vector>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rLog.hpp"

#include "rInput.hpp"
#include "input/rController.hpp"
#include "input/rTouch.hpp"

typedef std::map<unsigned int , rTouch*> rTouchMap;
typedef std::vector<rController*> rControllerArray;

class rInputManager : public rInput{
public:
	rTouch* CreateTouch(unsigned int id, const rPoint& position, rTouchType type = rTOUCH_DOWN);
	rTouch* GetTouch(unsigned int id);
	bool UpdateTouch(unsigned int id, const rPoint& position, rTouchType type);
	
	size_t TouchCount() const;
	void GetTouchIds(rIntArray& ids);
	virtual void GetTouches(rTouchArray& touches) const;
	
	rController* CreateController(unsigned int buttonCount, unsigned int dPadCount, unsigned int analogStickCount, unsigned int triggerCount);
	virtual size_t ControllerCount() const;
	virtual rControllerState* GetControllerState(size_t index) const;
	virtual rController* GetController(size_t index) const;
	
protected:
	void NotifyOfTouch(rTouch* touch);
	
protected:
	rTouchMap m_touches;
	rControllerArray m_controllers;
};

#endif
