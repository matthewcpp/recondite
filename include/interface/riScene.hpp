#ifndef RI_SCENE_HPP
#define RI_SCENE_HPP

#include "rBuild.hpp"

#include "rString.hpp"
#include "rLine3.hpp"

class rActor3;

class RECONDITE_API riScene{
public:
	virtual void AddActor(rActor3* actor) = 0;
	virtual rActor3* GetActor(const rString& name) const = 0;
	virtual size_t NumActors () const = 0;

	virtual void DeleteActor(const rString& name) = 0;
	virtual rActor3* RayPick(const rRay3& ray) = 0;
	virtual rActor3* ViewportPick(const rString& viewportName, int x, int y) = 0;
};

#endif