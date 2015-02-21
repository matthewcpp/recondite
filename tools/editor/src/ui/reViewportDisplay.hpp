#ifndef RE_VIEWPORTDISPLAY_HPP
#define RE_VIEWPORTDISPLAY_HPP

#include "project/reComponent.hpp"

#include "reViewport.hpp"

#include <wx/wx.h>
#include <wx/splitter.h>

#include "tools/reToolManager.hpp"

class reViewportDisplay : public wxPanel{
public:
	reViewportDisplay(reComponent* component, reToolManager* toolManager, wxWindow* parent, wxWindowID id = wxID_ANY);

public:
	reViewport* GetViewport(const wxString& name);

	virtual void UpdateDisplay();

private:
	void OnComponentInitialized(rEvent& event);
	void OnDisplayShouldUpdate(rEvent& event);

private:
	void CreateViewportDisplay();

private:
	reComponent* m_component;
	reToolManager* m_toolManager;

	reViewport* m_topLeftViewport;
	reViewport* m_topRightViewport;
	reViewport* m_bottomLeftViewport;
	reViewport* m_bottomRightViewport;

	wxSplitterWindow* m_leftSplitter;
	wxSplitterWindow* m_rightSplitter;
	wxSplitterWindow* m_mainSplitter;
};

#endif