#pragma once

#include <wx/wx.h>

#include "rwxGLCanvas.hpp"

#include "project/reComponent.hpp"

#include "rViewport.hpp"

class reModelViewerFrame : public wxFrame{
public:
	reModelViewerFrame(reComponent* component, wxWindow* parent);

	void CreateElements();

	void ViewModel(const wxString& name);

private:
	void OnClose(wxCloseEvent& event);

private:
	reComponent* _component;
	recondite::Camera* _camera;
	rwxGLCanvas* _glCanvas;
	rActor3* _currentActor;
};