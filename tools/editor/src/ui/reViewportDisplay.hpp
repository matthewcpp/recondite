#ifndef RE_VIEWPORTDISPLAY_HPP
#define RE_VIEWPORTDISPLAY_HPP

#include <wx/wx.h>
#include <wx/splitter.h>

#include "project/reComponent.hpp"
#include "ui/reViewport.hpp"

#include "tools/reToolManager.hpp"
#include "rePaletteDropTarget.hpp"

class reViewportDisplay : public reViewportManager, public wxPanel{
public:
	reViewportDisplay(reComponent* component, reToolManager* toolManager, wxWindow* parent, wxWindowID id = wxID_ANY);

public:
	reViewport* GetViewport(const wxString& name);
	reViewport* GetActiveViewport();

	virtual void UpdateAllViewports(bool force = false) override;
	virtual void MaximizeViewport(int id);
	virtual void RestoreViewports();
	virtual void HoverCanvas(rwxGLCanvas* canvas);

	void SetDefaultViewOrientations();

	void CharHook(wxKeyEvent& event);

private:
	void OnDisplayShouldUpdate(rEvent& event);
	void OnCommandProcessed(rEvent& event);

	void BindCanvasEvents(rwxGLCanvas* canvas);
	void OnViewportActivate(wxMouseEvent& event);
	void OnSceneLoadComplete(rEvent& event);

private:
	void CreateViewportDisplay();

	void SaveViewportLayout();

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

	std::pair<bool, int> m_splitterInfo[3];
	int m_sashPositions[3];
	bool m_isMaximized;
	rwxGLCanvas* m_hoverCanvas;

	wxLongLong m_lastUpdateTime;
};

#endif