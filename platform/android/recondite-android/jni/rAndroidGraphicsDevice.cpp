#include "rAndroidGraphicsDevice.hpp"

bool rAndroidGraphicsDevice::Init(android_app* state){
	EGLint w, h, dummy, format;

	// initialize OpenGL ES and EGL

	/*
	 * Here specify the attributes of the desired configuration.
	 * Below, we select an EGLConfig with at least 8 bits per color
	 * component compatible with on-screen windows
	 */
	const EGLint attribs[] = {
			EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
			EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
			EGL_BLUE_SIZE, 8,
			EGL_GREEN_SIZE, 8,
			EGL_RED_SIZE, 8,
			EGL_NONE
	};
	EGLint numConfigs;
	EGLConfig config;

	m_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

	eglInitialize(m_display, 0, 0);

	/* Here, the application chooses the configuration it desires. In this
	 * sample, we have a very simplified selection process, where we pick
	 * the first EGLConfig that matches our criteria */
	eglChooseConfig(m_display, attribs, &config, 1, &numConfigs);

	/* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
	 * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
	 * As soon as we picked a EGLConfig, we can safely reconfigure the
	 * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
	eglGetConfigAttrib(m_display, config, EGL_NATIVE_VISUAL_ID, &format);

	ANativeWindow_setBuffersGeometry(state->window, 0, 0, format);

	m_surface = eglCreateWindowSurface(m_display, config, state->window, NULL);

	EGLint contextAttrs[] = {
		 EGL_CONTEXT_CLIENT_VERSION, 2,
		 EGL_NONE
	};

	m_context = eglCreateContext(m_display, config, NULL, contextAttrs);

	if (eglMakeCurrent(m_display, m_surface, m_surface, m_context) == EGL_FALSE) {
		rLog::Error("Unable to eglMakeCurrent");
		return false;
	}



	eglQuerySurface(m_display, m_surface, EGL_WIDTH, &m_size.x);
	eglQuerySurface(m_display, m_surface, EGL_HEIGHT, &m_size.y);

	return rOpenGLGraphicsDevice::Init();
}

void rAndroidGraphicsDevice::Uninit(){
	if (m_display != EGL_NO_DISPLAY) {
		eglMakeCurrent(m_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		if (m_context != EGL_NO_CONTEXT) {
			eglDestroyContext(m_display, m_context);
		}
		if (m_surface != EGL_NO_SURFACE) {
			eglDestroySurface(m_display, m_surface);
		}
		eglTerminate(m_display);
	}

	m_display = EGL_NO_DISPLAY;
	m_context = EGL_NO_CONTEXT;
	m_surface = EGL_NO_SURFACE;

	rAndroidGraphicsDevice::Uninit();
}

void rAndroidGraphicsDevice::SwapBuffers(){
	eglSwapBuffers(m_display, m_surface);
}

rSize rAndroidGraphicsDevice::GetSize() const{
	return m_size;
}
