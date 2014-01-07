#ifndef R_SDLAPPLICATION_HPP
#define R_SDLAPPLICATION_HPP

#include "SDL.h"

#include "rApplication.hpp"
#include "rSDLGraphicsDevice.hpp"
#include "rOpenGLContentManager.hpp"

#include "ui/ruiLayoutManager.hpp"

#include "rViewport.hpp"
#include "rCamera.hpp"

//temp
#include "rAlignedBox3.hpp"
#include "ui/ruiPicker.hpp"

class rSDLApplication : public rApplication{
public:
	rSDLApplication();
	~rSDLApplication();

public:
	bool Init();
	void Uninit();

	virtual void Update();
	virtual void Draw();

	void ProcessEvent(SDL_Event& event);

	virtual unsigned long GetTimeMiliseconds() const;

	void TempInit();

protected:
	rSDLGraphicsDevice* m_graphicsDevice;
	rOpenGLContentManager* m_contentManager;

	ruiLayoutManager* m_layoutManager;

	rViewport m_viewport;
	rTargetCamera* m_camera;
};

#endif