#ifndef RE_VIEWPORTDISPLAY_HPP
#define RE_VIEWPORTDISPLAY_HPP

#include "project/reComponent.hpp"

#include "reViewport.hpp"

#include <wx/wx.h>
#include <wx/splitter.h>

#include "tools/reToolManager.hpp"
#include "rePaletteDropTarget.hpp"

class reViewportDisplay : public reViewportManager, public wxPanel{
public:
	reViewportDisplay(reComponent* component, reToolManager* toolManager, wxWindow* parent, wxWindowID id = wxID_ANY);

public:
	reViewport* GetViewport(const wxString& name);
	reViewport* GetActiveViewport();

	virtual void UpdateAllViewports();

private:
	void OnComponentInitialized(rEvent& event);
	void OnDisplayShouldUpdate(rEvent& event);

	void BindCanvasEvents(rwxGLCanvas* canvas);
	void OnViewportActivate(wxMouseEvent& event);

private:
	void CreateViewportDisplay();

private:
	reComponent* m_component;
	reToolManager* m_toolManager;

	reViewport* m_topLeftViewport;
	reViewport* m_topRightViewport;
	reViewport* m_bottomLeftViewport;
	reViewport* m_bottomRightViewport;

	reViewport* m_activeViewport;

	wxSplitterWindow* m_leftSplitter;
	wxSplitterWindow* m_rightSplitter;
	wxSplitterWindow* m_mainSplitter;
};

#endif