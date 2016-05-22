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
	virtual bool OnPointerDown(const rPoint& position);
	virtual bool OnPointerUp(const rPoint& position);
	virtual bool OnPointerMove(const rPoint& position);
	virtual bool OnPointerLeave(const rPoint& position);
	virtual bool OnPointerEnter(const rPoint& position);

private:
	void BindDefaultEvents();

	void OnMouseDown(rEvent& event);
	void OnMouseUp(rEvent& event);
	void OnMouseMotion(rEvent& event);
	void OnMouseLeave(rEvent& event);
	void OnMouseEnter(rEvent& event);

private:
	bool dragging;
};

#endif