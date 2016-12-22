#ifndef RI_SCENE_HPP
#define RI_SCENE_HPP

#include "rBuild.hpp"

#include "rString.hpp"
#include "rTypes.hpp"
#include "rLine3.hpp"

#include "rPickResult.hpp"

class rActor3;

class RECONDITE_API riScene{
public:
	virtual bool AddActor(rActor3* actor) = 0;
	virtual rActor3* GetActor(const rString& name) const = 0;
	virtual size_t NumActors () const = 0;
	virtual void GetActors(rArrayString& actors) const = 0;

	virtual rString GetDefaultActorId(const rString& prefix) = 0;

	virtual void DeleteActor(rActor3* actor) = 0;
	virtual void RayPick(const rRay3& ray, rPickResult& pickResult) = 0;
};

#endif