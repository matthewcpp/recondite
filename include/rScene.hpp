#ifndef R_SCENE_HPP
#define R_SCENE_HPP

#include <map>
#include <vector>
#include <cfloat>

#include "rBuild.hpp"

#include "interface/riScene.hpp"
#include "rActorSerialization.hpp"

#include "stream/rOStringStream.hpp"
#include "xml/rXMLDocument.hpp"

#include "rActor3.hpp"
#include "rEventHandler.hpp"

#include "rEvents.hpp"

class RECONDITE_API rScene : public rEventHandler, public riScene{
public:
	rScene(riComponent* component, rGraphicsDevice* graphicsDevice);
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

private:

	typedef std::map<rString, rActor3*> rActorMap;
	typedef std::vector<rActor3*> rActorArray;

private:
	rActorMap m_actors;

	riComponent* m_component;
	rGraphicsDevice* m_graphicsDevice;
};

#endif