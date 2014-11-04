#ifndef R_SCENE_HPP
#define R_SCENE_HPP

#include <map>
#include <vector>

#include "rBuild.hpp"

#include "interface/riScene.hpp"
#include "interface/riActorSerialization.hpp"

#include "stream/rIStream.hpp"
#include "xml/rXMLDocument.hpp"

#include "rActor3.hpp"

class RECONDITE_API rScene : public riScene{
public:
	void Update(rEngine& engine);
	void Draw(rEngine& engine);

	virtual void AddActor(rActor3* actor);
	virtual rActor3* GetActor(const rString& name) const;
	virtual size_t NumActors () const;

	virtual void DeleteActor(const rString& name);

	void Clear();

private:

	typedef std::map<rString, rActor3*> rActorMap;
	typedef std::vector<rActor3*> rActorArray;

private:
	rActorMap m_actors;
};

#endif