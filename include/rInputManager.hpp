#ifndef R_INPUTMANAGER_HPP
#define R_INPUTMANAGER_HPP

#include <map>
#include <vector>

#include "rBuild.hpp"
#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rLog.hpp"

#include "rInput.hpp"
#include "input/rController.hpp"
#include "input/rTouch.hpp"

#include "input/rMouse.hpp"
#include "input/rKeyboard.hpp"
#include "input/rGestureTracker.hpp"

#include "ui/ruiManager.hpp"

class RECONDITE_API rInputManager : public rInput{
public:

	rInputManager();
	void SetUIManager(ruiManager* uiManager);

	rTouch* CreateTouch(int id, const rPoint& position, rTouchType type = rTOUCH_DOWN);
	virtual rTouch* GetTouch(int id);
	bool UpdateTouch(int id, const rPoint& position, rTouchType type);
	virtual size_t TouchCount() const;

	void CreateMouseMotionEvent(int x, int y);
	void CreateMouseButtonEvent(rMouseButton button, rButtonState state, const rPoint& position);
	void CreateMouseWheelEvent(rMouseWheelDirection direction);

	void CreateKeyboardEvent(rKey key, rKeyState state);

	virtual const rMouseState* GetMouseState() const;
	virtual const rKeyboardState* Keyboard() const;
	
	void GetTouchIds(rIntArray& ids);
	
	rController* CreateController(unsigned int buttonCount, unsigned int dPadCount, unsigned int analogStickCount, unsigned int triggerCount);
	virtual size_t ControllerCount() const;
	virtual rControllerState* GetControllerState(size_t index) const;
	virtual rController* GetController(size_t index) const;
	
	virtual const riGestureTracker* Gestures() const;
	virtual void PostUpdate();

private:

	typedef std::map<unsigned int , rTouch*> rTouchMap;
	typedef std::vector<rController*> rControllerArray;

private:
	rTouchMap m_touches;
	rControllerArray m_controllers;
	rGestureTracker m_gestures;

	ruiManager* m_ui;

	rMouse m_mouse;
	rKeyboard m_keyboard;
};

#endif
