#ifndef R_ANDROIDGRAPHICSDEVICE_HPP
#define R_ANDROIDGRAPHICSDEVICE_HPP

#include <jni.h>
#include <errno.h>

#include <android/log.h>
#include <android_native_app_glue.h>

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "rOpenGLGraphicsDevice.hpp"

class rAndroidGraphicsDevice : public rOpenGLGraphicsDevice{
public:
	virtual bool Init(android_app* state);
	virtual void Uninit();

	virtual void SwapBuffers();
	rSize GetSize() const;

private:
    EGLDisplay m_display;
    EGLSurface m_surface;
    EGLContext m_context;

    rSize m_size;
};

#endif
