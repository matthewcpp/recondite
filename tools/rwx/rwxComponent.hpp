#ifndef RWX_COMPONENT_HPP
#define RWX_COMPONENT_HPP

#include "rwxOpenGLGraphicsDevice.hpp"

#include "wx/wx.h"
#include "wx/glcanvas.h"
#include "wx/stdpaths.h"

#include "rBuild.hpp"

#include "rComponent.hpp"
#include "platform/rgl/rOpenGLContentManager.hpp"

class RECONDITE_RWX_CLASS rwxComponent : public rComponent{
public:
	rwxComponent();

	virtual rSize DisplaySize() const;
	virtual unsigned long GetTimeMiliseconds() const;

	rwxOpenGLGraphicsDevice* GraphicsDevice();
	rOpenGLContentManager* ContentManager();
	rInputManager* InputManager();

	wxGLContext* GetContext();

	virtual void RenderScene(rViewport* viewport);

	virtual rString GetBasePath();

public:
	virtual bool Init(wxGLCanvas* canvas);

private:
	rwxOpenGLGraphicsDevice* m_rwxGraphicsDevice;
	rOpenGLContentManager* m_rglContentManager;
	rInputManager* m_rInputManager;
};

#endif