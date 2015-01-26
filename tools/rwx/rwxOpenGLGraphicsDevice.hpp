#ifndef RWX_OPENGLGRAPHICSDEVICE_HPP
#define RWX_OPENGLGRAPHICSDEVICE_HPP

#include <GL/glew.h>

#include "wx/wx.h"
#include "wx/glcanvas.h"

#include "rgl/rOpenGLGraphicsDevice.hpp"

class rwxOpenGLGraphicsDevice : public rOpenGLGraphicsDevice{
public:
	rwxOpenGLGraphicsDevice();

public:
	virtual bool Init(wxGLCanvas* canvas);
	virtual void SwapBuffers();

private:
	wxGLContext* m_wxGLContext;
};

#endif