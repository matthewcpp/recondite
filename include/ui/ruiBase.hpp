#ifndef RUI_BASE_HPP
#define RUI_BASE_HPP

#include "rBuild.hpp"

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "input/rMouse.hpp"
#include "input/rKeyboard.hpp"

class RECONDITE_API ruiWidget;

class RECONDITE_API ruiInput{
public:
	virtual bool InjectTouchDown(const rTouch& touch) = 0;
	virtual bool InjectTouchMove(const rTouch& touch) = 0;
	virtual bool InjectTouchUp(const rTouch& touch) = 0;

	virtual bool InjectMouseDownEvent(rMouseButton button, const rMouseState& mouse) = 0;
	virtual bool InjectMouseUpEvent(rMouseButton button, const rMouseState& mouse) = 0;
	virtual bool InjectMouseMotionEvent(const rMouseState& mouse) = 0;
	virtual bool InjectMouseWheelEvent(rMouseWheelDirection direction, const rMouseState& mouse) = 0;

	
	virtual bool InjectKeyDownEvent(rKey key, rKeyboardState& state) = 0;
	virtual bool InjectKeyUpEvent(rKey key, rKeyboardState& state) = 0;
};

class RECONDITE_API ruiIOverlay {
public:
	virtual void ShowModal(ruiWidget* widget) = 0;
	virtual void EndModal(ruiWidget* widget) = 0;
};

class RECONDITE_API ruiIControlWithOptions {
public:
	virtual const rArrayString& Options() const = 0;

	virtual size_t SelectionIndex() const = 0;
	virtual bool SetSelectionIndex(size_t index) = 0;
};

#endif
