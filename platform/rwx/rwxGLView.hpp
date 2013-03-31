#ifndef RWX_GL_VIEW_HPP
#define RWX_GL_VIEW_HPP

#include "recondite.hpp"
#include "rEngine.hpp"

#include "wx/wx.h"
#include "wx/glcanvas.h"


class rwxGLView : public wxGLCanvas{
public:
	rwxGLView(rEngine* engine, wxWindow* parent, wxWindowID id=wxID_ANY, const int *attribList = NULL, const wxPoint& pos = wxDefaultPosition, const wxSize& size=wxDefaultSize, long style = 0, const wxString& name = "GLCanvas", const wxPalette& palette = wxNullPalette);
	
	~rwxGLView();
	void SetCamera(rCamera* camera);
        
        virtual void DrawScene() =0;
        virtual void DrawReconditeScene();
    
protected:
	bool InitGraphicsDeviceIfNecessary();
	void SetViewportSize();
	void PrepareToDraw();
	
	rViewport m_viewport;
	rEngine* m_engine;
	
	rViewCamera* m_camera;
        
        void OnPaint(wxPaintEvent& event);
	
protected:
	static bool InitSharedContextIfNecessary(wxGLCanvas* glCanvas);
	static wxGLContext* sharedContext;
        
        DECLARE_EVENT_TABLE();
};

#endif