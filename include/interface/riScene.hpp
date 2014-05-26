#ifndef RI_SCENE_HPP
#define RI_SCENE_HPP

#include "rBuild.hpp"

#include "rString.hpp"

class rActor3;

class RECONDITE_API  riScene{
public:
	virtual void AddActor(rActor3* actor) = 0;
	virtual rActor3* GetActor(const rString& name) const = 0;
	virtual size_t NumActors () const = 0;

	virtual void DeleteActor(const rString& name) = 0;
};

#endif