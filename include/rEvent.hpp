#ifndef R_EVENT_HPP
#define R_EVENT_HPP

#include "rBuild.hpp"

class RECONDITE_API rEvent {
public:
	rEvent() : m_handled(false) {}
	void SetHandled(bool handled = true) {m_handled = handled;}
	bool Handled() const { return m_handled; }

private:
	bool m_handled;
};

typedef void(*rEventFunctionPointer)(rEvent&);

#endif