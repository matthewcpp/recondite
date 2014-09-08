#ifndef RUI_DEFAULT_EVENT_HANDLER
#define RUI_DEFAULT_EVENT_HANDLER

#include "rBuild.hpp"

#include "rPoint.hpp"
#include "rEventHandler.hpp"
#include "ruiEvents.hpp"

class RECONDITE_API ruiDefaultEventHandler : public rEventHandler{
public:
	ruiDefaultEventHandler();

protected:
	virtual void OnPointerDown(const rPoint& position) {}
	virtual void OnPointerUp(const rPoint& position) {}
	virtual void OnPointerLeave(const rPoint& position) {}
	virtual void OnPointerEnter(const rPoint& position) {}

private:
	void BindDefaultEvents();

	void OnMouseDown(rEvent& event);
	void OnMouseUp(rEvent& event);
	void OnMouseLeave(rEvent& event);
	void OnMouseEnter(rEvent& event);
};

#endif