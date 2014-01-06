#ifndef R_SDLGRAPHICSDEVICE_HPP
#define R_SDLGRAPHICSDEVICE_HPP

#include <GL/glew.h>

#include "SDL.h"

#include "rOpenGLGraphicsDevice.hpp"

class rSDLGraphicsDevice : public rOpenGLGraphicsDevice{
public:
	virtual bool Init();
	virtual void SwapBuffers();
};

#endif