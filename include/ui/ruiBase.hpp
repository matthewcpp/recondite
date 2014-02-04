#ifndef RUI_BASE_HPP
#define RUI_BASE_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

class ruiWidget;

class ruiInput{
public:
	virtual bool InjectTouchDown(const rTouch& touch) = 0;
	virtual bool InjectTouchMove(const rTouch& touch) = 0;
	virtual bool InjectTouchUp(const rTouch& touch) = 0;

	virtual bool InjectMouseDownEvent(rMouseButton button, const rMouseState& mouse) = 0;
	virtual bool InjectMouseUpEvent(rMouseButton button, const rMouseState& mouse) = 0;
	virtual bool InjectMouseMotionEvent(const rMouseState& mouse) = 0;
	virtual bool InjectMouseWheelEvent(rMouseWheelDirection direction, const rMouseState& mouse) = 0;
};

class ruiIOverlay {
public:
	virtual void ShowModal(ruiWidget* widget) = 0;
	virtual void EndModal(ruiWidget* widget) = 0;
};

class ruiIControlWithOptions {
public:
	virtual const rArrayString& Options() const = 0;

	virtual size_t SelectionIndex() const = 0;
	virtual bool SetSelectionIndex(size_t index) = 0;
};

#endif
