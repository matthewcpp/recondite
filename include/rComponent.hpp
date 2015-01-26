#ifndef R_COMPONENT_HPP
#define R_COMPONENT_HPP

#include "rBuild.hpp"

#include "rLog.hpp"
#include "rEngine.hpp"
#include "rScene.hpp"
#include "rInputManager.hpp"
#include "ui/ruiOverlayManager.hpp"

#include "interface/riComponent.hpp"

class RECONDITE_API rComponent : public riComponent{
public:
	rComponent();
	virtual unsigned long GetTimeMiliseconds() const = 0;

	virtual bool Init();
	virtual void Uninit();

	bool IsReady() const;

	virtual void LoadScene(const rString& name);

public:
	virtual rViewport* CreateViewport(const rString& name);
	virtual rViewport* GetViewport(const rString& name) const;
	virtual void DeleteViewport(const rString& name);
	virtual size_t NumViewports() const;

public:
	virtual void RegisterActorLoader(const rString& className, riActorLoader* actorLoader);
	virtual void UnregisterActorLoader(const rString& className);

protected:
	virtual void InitEngine(rGraphicsDevice* graphics, rContentManager* content, rInputManager* input);

protected:
	typedef std::map<rString, riActorLoader*> rActorLoaderMap;
	typedef std::map<rString, riActorSerializer*> rActorSerializerMap;
	typedef std::map<rString, rViewport*> rViewportMap;

protected:

	rEngine m_engine;
	rScene* m_scene;

	rGraphicsDevice* m_graphicsDevice;
	ruiOverlayManager* m_overlayManager;

	rViewportMap m_viewports;

	bool m_isReady;

private:
	rActorLoaderMap m_actorLoaders;
	rActorSerializerMap m_actorSerializers;

	
};

#endif