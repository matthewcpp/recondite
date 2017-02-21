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

protected:
	virtual void InitEngine(rGraphicsDevice* graphics, rContentManager* content, rInputManager* input, 
		rFileSystem* fileSystem, recondite::ResourceManager* resourceManager);
	virtual void InitDefaultActorClasses();
	bool SaveSceneXML(const rString& path);

protected:

	rEngine* m_engine;

	rGraphicsDevice* m_graphicsDevice;
	rFileSystem* m_fileSystem;

	bool m_isReady;
};

#endif