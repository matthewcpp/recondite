#ifndef R_COMPONENT_HPP
#define R_COMPONENT_HPP

#include "rBuild.hpp"

#include "rLog.hpp"
#include "rEngine.hpp"
#include "rScene.hpp"
#include "rInputManager.hpp"
#include "ui/ruiManager.hpp"
#include "rActorFactory.hpp"

#include "interface/riSerialization.hpp"

#include "rEventHandler.hpp"
#include "rEvents.hpp"

class RECONDITE_API rComponent : public rEventHandler{
public:
	rComponent();
	virtual unsigned long GetTimeMiliseconds() const = 0;

	virtual bool Init();
	virtual bool LoadDefaultResources();
	virtual void Uninit();

	bool IsReady() const;

	virtual void LoadScene(const rString& name);
	virtual bool SaveScene(const rString& path);
	virtual void ClearScene();

	rEngine* GetEngine();
	rScene* GetScene();

	virtual rString GetBasePath() = 0;

public:
	virtual void AddActorClass(const rString& name, rActorFactory::ActorFunction func);

protected:
	virtual void InitEngine(rGraphicsDevice* graphics, rContentManager* content, rInputManager* input, rFileSystem* fileSystem);
	virtual void InitDefaultActorClasses();
	bool SaveSceneXML(const rString& path);

protected:

	rEngine m_engine;
	rScene* m_scene;

	rGraphicsDevice* m_graphicsDevice;
	ruiManager* m_uiManager;
	rFileSystem* m_fileSystem;

	bool m_isReady;

private:
	rActorFactory m_actorFactory;
};

#endif