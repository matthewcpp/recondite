#include "rSDLGraphicsDevice.hpp"

bool rSDLGraphicsDevice::Init(){
    GLenum err = glewInit();

	glEnable(GL_PROGRAM_POINT_SIZE);
    
	return rOpenGLGraphicsDevice::Init();
}

void rSDLGraphicsDevice::SwapBuffers(){
	SDL_GL_SwapBuffers();
}