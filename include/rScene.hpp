#ifndef R_SCENE_HPP
#define R_SCENE_HPP

#include <map>
#include <vector>
#include <cfloat>

#include "rBuild.hpp"

#include "interface/riScene.hpp"
#include "rActorFactory.hpp"

#include "stream/rOStringStream.hpp"
#include "xml/rXMLDocument.hpp"

#include "rActor3.hpp"
#include "rEventHandler.hpp"

#include "rEvents.hpp"

#include "interface/riSerialization.hpp"

class RECONDITE_API rScene : public rEventHandler, public riScene, public riSerializable{
public:
	rScene(rEngine* engine);
	~rScene();

public:
	void Update();
	void Draw();

	virtual void AddActor(rActor3* actor);
	virtual rActor3* GetActor(const rString& name) const;
	virtual size_t NumActors () const;

	virtual void DeleteActor(const rString& name);

	virtual rString GetDefaultActorId(const rString& prefix);

	virtual rActor3* RayPick(const rRay3& ray);
	virtual rActor3* ViewportPick(const rString& viewportName, int x, int y);

	void Clear();

	virtual bool Save(riSerializationTarget* target);
	virtual bool Load(riSerializationTarget* target);

private:

	typedef std::map<rString, rActor3*> rActorMap;
	typedef std::vector<rActor3*> rActorArray;

private:
	rActorMap m_actors;
	rEngine* m_engine;
};

#endif