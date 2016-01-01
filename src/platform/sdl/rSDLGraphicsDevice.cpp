#include "sdl/rSDLGraphicsDevice.hpp"

rSDLGraphicsDevice::rSDLGraphicsDevice(SDL_Window* window) {
	m_window = window;
}

bool rSDLGraphicsDevice::Init(){
    GLenum err = glewInit();

	glEnable(GL_PROGRAM_POINT_SIZE);
    
	return rOpenGLGraphicsDevice::Init();
}

void rSDLGraphicsDevice::SwapBuffers(){
	SDL_GL_SwapWindow(m_window);
}