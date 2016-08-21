#ifndef R_SDLAPPLICATION_HPP
#define R_SDLAPPLICATION_HPP

#include "SDL.h"

#include "rSDLBuild.hpp"

#include "rFileSystem.hpp"

#include "rApplicationBase.hpp"
#include "rSDLGraphicsDevice.hpp"
#include "platform/rgl/rOpenGLContentManager.hpp"
#include "rSDLInputManager.hpp"

#include "ui/ruiManager.hpp"

#include "rViewport.hpp"
#include "rCamera.hpp"

#include "platform/sdl/rSDLMain.hpp"

class RECONDITE_SDL_API rApplication : public rApplicationBase{
public:
	rApplication();
	~rApplication();

public:
	virtual bool Init();
	virtual void Uninit();

	void ProcessEvent(SDL_Event& event);

	virtual unsigned long GetTimeMiliseconds() const;

	virtual rString GetBasePath();

protected:
	rSDLGraphicsDevice* m_graphicsDevice;
	rOpenGLContentManager* m_contentManager;
	rSDLInputManager* m_inputManager;

	rString m_basePath;

	SDL_Window* m_window;
	SDL_GLContext m_glContext;
};

#endif