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
typedef std::vector<rInputListener*> rInputListenerArray;

class rInputManager : public rInput{
public:
	rTouch* CreateTouch(int id, const rPoint& position, rTouchType type = rTOUCH_DOWN);
	virtual rTouch* GetTouch(int id);
	bool UpdateTouch(int id, const rPoint& position, rTouchType type);
	
	size_t TouchCount() const;
	void GetTouchIds(rIntArray& ids);
	virtual void GetTouches(rTouchArray& touches) const;
	
	rController* CreateController(unsigned int buttonCount, unsigned int dPadCount, unsigned int analogStickCount, unsigned int triggerCount);
	virtual size_t ControllerCount() const;
	virtual rControllerState* GetControllerState(size_t index) const;
	virtual rController* GetController(size_t index) const;
	
	void AddListener(rInputListener* listener);
	void RemoveListener(rInputListener* listener);

protected:
	void NotifyOfTouch(const rTouch& touch);
	
protected:
	rTouchMap m_touches;
	rControllerArray m_controllers;
	rInputListenerArray m_listeners;
};

#endif
