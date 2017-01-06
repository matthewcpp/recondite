#ifndef R_SCENE_HPP
#define R_SCENE_HPP

#include <map>
#include <vector>
#include <cfloat>

#include "rBuild.hpp"

#include "interface/riScene.hpp"
#include "rActorFactory.hpp"

#include "xml/rXMLDocument.hpp"

#include "rActor3.hpp"
#include "rEventHandler.hpp"

#include "rEvents.hpp"

#include "interface/riSerialization.hpp"

#include "rLog.hpp"

class RECONDITE_API rScene : public rEventHandler, public riScene, public riSerializable{
public:
	rScene(rEngine* engine);
	~rScene();

public:
	void Update();
	void Draw();

	virtual bool AddActor(rActor3* actor) override;
	virtual rActor3* GetActor(const rString& name) const;
	virtual size_t NumActors () const;
	virtual void GetActors(rArrayString& names) const;

	virtual void EachActor(std::function<void(rActor3*)> func);

	virtual void DeleteActor(rActor3* actor);
	bool RenameActor(const rString& oldId, const rString& newId);

	virtual rString GetDefaultActorId(const rString& prefix);

	virtual void RayPick(const rRay3& ray, rPickResult& pickResult);

	void Clear();

	virtual bool Save(riSerializationTarget* target);
	virtual bool Load(riSerializationTarget* target);
	virtual bool ParseActors(riSerializationTarget* target);

	bool IsLoading() const;

	void Flush();

	rAlignedBox3 GetBounding();

private:

	typedef std::map<rString, rActor3*> rActorMap;

private:
	rActorMap m_actors;
	std::set<rActor3*> m_ActorsToDelete;

	rEngine* m_engine;

	bool m_isLoading;
};

#endif