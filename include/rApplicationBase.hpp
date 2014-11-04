#ifndef R_APPLICATION_HPP
#define R_APPLICATION_HPP

#include "rBuild.hpp"

#include "rEngine.hpp"
#include "rModule.hpp"
#include "rGraphicsDevice.hpp"
#include "rInputManager.hpp"
#include "rScene.hpp"

#include "interface/riApplication.hpp"

class RECONDITE_API rApplicationBase : public riApplication{
public:
	virtual unsigned long GetTimeMiliseconds() const = 0;
	virtual void Update();
	virtual void Draw();

public:
	rApplicationBase();
	virtual ~rApplicationBase();

	virtual bool Init();
	virtual void Uninit();

	bool IsRunning() const;

	virtual void Tick();

	virtual size_t TargetFPS() const;
	void SetTargetFPS(unsigned int targetFPS);

	void SetDisplaySize(int width, int height);
	virtual rSize DisplaySize() const;

	virtual size_t FrameCount() const;

	virtual void LoadScene(const rString& name);

public:
	virtual rModule* CreateModule() = 0;

public:

	virtual rViewport* CreateViewport(const rString& name);
	virtual rViewport* GetViewport(const rString& name) const;
	virtual void DeleteViewport(const rString& name);
	virtual size_t NumViewports() const;

public:

	virtual void RegisterActorLoader(const rString& className, riActorLoader* actorLoader);
	virtual void UnregisterActorLoader(const rString& className);

private:
	typedef std::map<rString, riActorLoader*> rActorLoaderMap;
	typedef std::map<rString, riActorSerializer*> rActorSerializerMap;

protected:
	void InitEngine(rGraphicsDevice* graphics, rContentManager* content, rInputManager* input);
	void InitModule();

protected:
	typedef std::map<rString, rViewport*> rViewportMap;

protected:
	bool m_isRunning;
	unsigned int m_targetFPS;
	size_t m_frameCount;

	rEngine m_engine;
	rModule* m_module;
	rScene* m_scene;

	rGraphicsDevice* m_graphicsDevice;
	ruiOverlayManager* m_overlayManager;

	rSize m_displaySize;

	rViewportMap m_viewports;

private:
	rActorLoaderMap m_actorLoaders;
	rActorSerializerMap m_actorSerializers;
};

#endif
