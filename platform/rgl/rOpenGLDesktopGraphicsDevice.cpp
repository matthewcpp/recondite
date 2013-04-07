#include "rOpenGLDesktopGraphicsDevice.hpp"

bool rOpenGLDesktopGraphicsDevice::Init(){
    GLenum err = glewInit();
    
    if (err == GLEW_OK){
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glEnable(GL_PERSPECTIVE_CORRECTION_HINT);

		glEnableClientState(GL_VERTEX_ARRAY);

		glColor4ub(255,255,255,255);

		glPointSize(4.0f);
		m_isInit = true;
    }
	else{
		m_isInit = false;
	}
	
	return m_isInit
}