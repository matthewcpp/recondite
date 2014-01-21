#ifndef R_SDLAPPLICATION_HPP
#define R_SDLAPPLICATION_HPP

#include "SDL.h"

#include "rApplication.hpp"
#include "rSDLGraphicsDevice.hpp"
#include "rOpenGLContentManager.hpp"
#include "rSDLInputManager.hpp"

#include "ui/ruiLayoutManager.hpp"

#include "rViewport.hpp"
#include "rCamera.hpp"

class rSDLApplication : public rApplication{
public:
	rSDLApplication(rModule* module);
	~rSDLApplication();

public:
	bool Init();
	void Uninit();

	void ProcessEvent(SDL_Event& event);

	virtual unsigned long GetTimeMiliseconds() const;

protected:
	rSDLGraphicsDevice* m_graphicsDevice;
	rOpenGLContentManager* m_contentManager;
	rSDLInputManager* m_inputManager;


};

#endif