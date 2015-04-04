#ifndef R_COMPONENT_HPP
#define R_COMPONENT_HPP

#include "rBuild.hpp"

#include "rLog.hpp"
#include "rEngine.hpp"
#include "rScene.hpp"
#include "rInputManager.hpp"
#include "ui/ruiOverlayManager.hpp"
#include "rActorFactory.hpp"

#include "interface/riComponent.hpp"
#include "interface/riSerialization.hpp"

#include "rEventHandler.hpp"
#include "rEvents.hpp"

#include "xml/rXMLDocument.hpp"
#include "xml/rXMLSerialization.hpp"

class RECONDITE_API rComponent : public rEventHandler, public riComponent{
public:
	rComponent();
	virtual unsigned long GetTimeMiliseconds() const = 0;

	virtual bool Init();
	virtual void Uninit();

	bool IsReady() const;

	virtual void LoadScene(const rString& name);
	virtual bool SaveScene(const rString& path);
	virtual void ClearScene();

	rEngine* GetEngine();
	rScene* GetScene();

public:
	virtual rViewport* CreateViewport(const rString& name);
	virtual rViewport* GetViewport(const rString& name) const;
	virtual void GetViewportNames(rArrayString& names) const;
	virtual void DeleteViewport(const rString& name);
	virtual size_t NumViewports() const;

public:
	virtual void AddActorClass(const rString& name, rActorFactory::ActorFunction func);

protected:
	virtual void InitEngine(rGraphicsDevice* graphics, rContentManager* content, rInputManager* input);
	virtual void InitDefaultActorClasses();
	bool SaveSceneXML(const rString& path, std::function<bool(rActor3*)> filterFunc);

protected:
	typedef std::map<rString, rViewport*> rViewportMap;

protected:

	rEngine m_engine;
	rScene* m_scene;

	rGraphicsDevice* m_graphicsDevice;
	ruiOverlayManager* m_overlayManager;

	rViewportMap m_viewports;

	bool m_isReady;

private:
	rActorFactory m_actorFactory;
};

#endif