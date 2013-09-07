#ifndef R_ANDROIDGRAPHICSDEVICE_HPP
#define R_ANDROIDGRAPHICSDEVICE_HPP

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "rOpenGLGraphicsDevice.hpp"

class rAndroidGraphicsDevice : public rOpenGLGraphicsDevice{
public:
	virtual bool Init(struct android_app* state);
	virtual bool Uninit();

	virtual void SwapBuffers();

private:
    EGLDisplay m_display;
    EGLSurface m_surface;
    EGLContext m_context;

    rSize& m_size;
};

#endif
