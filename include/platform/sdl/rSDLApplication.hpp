#ifndef R_SDLAPPLICATION_HPP
#define R_SDLAPPLICATION_HPP

#include "SDL.h"

#include "rBuild.hpp"

#include "rFileSystem.hpp"

#include "rApplicationBase.hpp"
#include "rSDLGraphicsDevice.hpp"
#include "rgl/rOpenGLContentManager.hpp"
#include "rSDLInputManager.hpp"

#include "ui/ruiOverlayManager.hpp"

#include "rViewport.hpp"
#include "rCamera.hpp"

#include "sdl/rSDLMain.hpp"

class RECONDITE_API rApplication : public rApplicationBase{
public:
	rApplication();
	~rApplication();

public:
	virtual bool Init();
	virtual void Uninit();

	void ProcessEvent(SDL_Event& event);

	virtual unsigned long GetTimeMiliseconds() const;

protected:
	rSDLGraphicsDevice* m_graphicsDevice;
	rOpenGLContentManager* m_contentManager;
	rSDLInputManager* m_inputManager;


};

#endif