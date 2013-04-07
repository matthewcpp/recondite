#ifndef R_OPENGL_DESKTOP_GRAPHICSDEVICE_HPP
#define R_OPENGL_DESKTOP_GRAPHICSDEVICE_HPP

#include <GL/glew.h>

#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
#endif

#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include "rOpenGLGraphicsDevice.hpp"

class rOpenGLDesktopGrapicsDevice : public rOpenGLGraphicsDevice {
public:
	virtual bool Init();
private:
};

#endif