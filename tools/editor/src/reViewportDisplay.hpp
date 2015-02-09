#ifndef RE_VIEWPORTDISPLAY_HPP
#define RE_VIEWPORTDISPLAY_HPP

#include "rwxComponent.hpp"

#include "reViewport.hpp"

#include <wx/wx.h>
#include <wx/splitter.h>

class reViewportDisplay : public wxPanel{
public:
	reViewportDisplay(rwxComponent* component, wxWindow* parent, wxWindowID id =wxID_ANY);

public:
	reViewport* GetViewport(const wxString& name);

private:
	void CreateViewportDisplay();

private:
	rwxComponent* m_component;

	reViewport* m_topLeftViewport;
	reViewport* m_topRightViewport;
	reViewport* m_bottomLeftViewport;
	reViewport* m_bottomRightViewport;

	wxSplitterWindow* m_leftSplitter;
	wxSplitterWindow* m_rightSplitter;
	wxSplitterWindow* m_mainSplitter;
};

#endif