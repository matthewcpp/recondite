#ifndef RE_MAINFRAME_HPP
#define RE_MAINFRAME_HPP

#include "wx/wx.h"

class reMainFrame : public wxFrame{
public:
	reMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
};

#endif