#ifndef FAKE_EVENT_LISTENER_HPP
#define FAKE_EVENT_LISTENER_HPP

#include "rEvent.hpp"

class FakeEventListener{
public:
	FakeEventListener() : m_callbackCalled(false) {}

	void EventCallback(rEvent& event){m_callbackCalled = true;}

	void HandleCallback(rEvent& event){
		event.SetHandled();
		m_callbackCalled = true;
	}

	bool CallbackCalled() const {return m_callbackCalled;}
	void Reset() {m_callbackCalled = false;}

private:
	bool m_callbackCalled;
};

#endif