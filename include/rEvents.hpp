#ifndef R_EVENTS_HPP
#define R_EVENTS_HPP

#include "rBuild.hpp"
#include "rEvent.hpp"

class rActor3;

class RECONDITE_API rActor3Event : public rEvent{
public:
	rActor3Event(rActor3* actor) : m_actor(actor) {}

	rActor3* Actor() { return m_actor; }

private:
	rActor3* m_actor;
};

class RECONDITE_API rActor3RenameEvent : public rActor3Event {
public:
	rActor3RenameEvent(rActor3* actor, const rString& previousId) : rActor3Event(actor), m_previousId(previousId) {}

	rString PreviousId() const { return m_previousId; }

private:
	rString m_previousId;
};

enum rEventType{
	rEVT_SCENE_ACTOR_ADDED,
	rEVT_SCENE_ACTOR_REMOVED,
	rEVT_SCENE_ACTOR_RENAMED,
	rEVT_SCENE_CLEAR,
	rEVT_SCENE_LOAD_BEGIN,
	rEVT_SCENE_LOAD_END
};

#endif