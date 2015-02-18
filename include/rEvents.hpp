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

enum rEventType{
	rEVT_COMPONENT_INITIALIZED,

	rEVT_SCENE_ACTOR_ADDED,
	rEVT_SCENE_ACTOR_REMOVED,
	rEVT_SCENE_LOAD_BEGIN,
	rEVT_SCENE_LOAD_END
};

#endif