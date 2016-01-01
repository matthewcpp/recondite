#ifndef R_SDLGRAPHICSDEVICE_HPP
#define R_SDLGRAPHICSDEVICE_HPP

#include <GL/glew.h>

#include "SDL.h"

#include "rgl/rOpenGLGraphicsDevice.hpp"

class rSDLGraphicsDevice : public rOpenGLGraphicsDevice{
public:
	rSDLGraphicsDevice(SDL_Window* window);

public:
	virtual bool Init();
	virtual void SwapBuffers();

private:
	SDL_Window* m_window;
};

#endif