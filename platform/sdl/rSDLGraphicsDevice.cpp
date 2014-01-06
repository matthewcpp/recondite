#include "rSDLGraphicsDevice.hpp"

bool rSDLGraphicsDevice::Init(){
    GLenum err = glewInit();
    
	return rOpenGLGraphicsDevice::Init();
}

void rSDLGraphicsDevice::SwapBuffers(){
	SDL_GL_SwapBuffers();
}