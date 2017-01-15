#ifndef RWX_GLCANVAS_HPP
#define RWX_GLCANVAS_HPP

//note this must be included before GL canvas because glew.h must be included before gl.h
#include "rwxComponent.hpp"

#include "wx/wx.h"
#include "wx/glcanvas.h"

#include "recondite.hpp"

class RECONDITE_RWX_CLASS rwxGLCanvas : public wxGLCanvas{
public:
	rwxGLCanvas(rwxComponent* component, const wxString& name, wxWindow *parent, wxWindowID id = wxID_ANY);
	~rwxGLCanvas();

	void OnPaint(wxPaintEvent& event);

	rViewport* GetViewport();
	recondite::Camera* GetCamera();

	wxString GetCanvasName() const;

protected:
	virtual void Render();

private:
	void CreateViewport();


protected:
	rwxComponent* m_component;

	wxString m_name;
	rViewport* m_viewport;
	recondite::Camera* m_camera;
};

class RECONDITE_RWX_CLASS rwxGLImageCanvas : public rwxGLCanvas {
public:
	rwxGLImageCanvas(rwxComponent* component, const wxString& name, wxWindow *parent, wxWindowID id = wxID_ANY);

public:
	virtual wxImage GetImage();

protected:
	virtual void Render();

private:
	wxImage _image;
};

#endif