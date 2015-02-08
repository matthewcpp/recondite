   #include "rwxOpenGLGraphicsDevice.hpp"

rwxOpenGLGraphicsDevice::rwxOpenGLGraphicsDevice(){
	m_wxGLContext = NULL;
}
   
bool rwxOpenGLGraphicsDevice::Init(wxGLCanvas* canvas){
	m_wxGLContext = new wxGLContext(canvas);
	canvas->SetCurrent(*m_wxGLContext);

	GLenum err = glewInit();

	glEnable(GL_PROGRAM_POINT_SIZE);

	return rOpenGLGraphicsDevice::Init();
}

wxGLContext* rwxOpenGLGraphicsDevice::GetContext(){
	return m_wxGLContext;
}

void rwxOpenGLGraphicsDevice::SwapBuffers(){}