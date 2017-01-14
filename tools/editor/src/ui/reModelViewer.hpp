#pragma once

#include <wx/wx.h>

#include "rwxGLCanvas.hpp"

#include "project/reComponent.hpp"

#include "rViewport.hpp"

class reModelViewerPanel : public wxPanel {
public:
	reModelViewerPanel(reComponent* component, const wxString& name, wxWindow* parent);

public:
	bool ViewModel(const wxString& name);
	void ClearModel();

private:
	void CreateElements(const wxString& name);


private:
	reComponent* _component;
	recondite::Camera* _camera;
	rwxGLCanvas* _glCanvas;
	rActor3* _currentActor;
};

class reModelViewerFrame : public wxFrame{
public:
	reModelViewerFrame(reComponent* component, wxWindow* parent);

public:
	bool ViewModel(const wxString& name);

private:
	void CreateElements(reComponent* component);
	void OnClose(wxCloseEvent& event);

private:
	reModelViewerPanel* _modelViewer;
};

class reModelViewerDialog : public wxDialog {
public:
	reModelViewerDialog(reComponent* component, const wxString& name);

private:
	void CreateElements(reComponent* component);
	void OnClose(wxCloseEvent& event);
	void OnButton(wxCommandEvent& event);

private:
	reModelViewerPanel* _modelViewer;
};