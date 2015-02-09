#ifndef RE_OUTLINER_HPP
#define RE_OUTLINER_HPP

#include "rwxComponent.hpp"

#include <wx/wx.h>
#include <wx/dataview.h>

class reOutliner : public wxDataViewTreeCtrl{
public:
	reOutliner(rwxComponent* component, wxWindow* parent, wxWindowID id = wxID_ANY);

private:
	rwxComponent* m_component;
};

#endif