#ifndef RI_SCENE_HPP
#define RI_SCENE_HPP

#include "rString.hpp"

class rActor3;

class riScene{
public:
	virtual void AddActor(rActor3* actor) = 0;
	virtual rActor3* GetActor(const rString& name) const = 0;

	virtual void DeleteActor(const rString& name) = 0;
};

#endif