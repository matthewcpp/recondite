#ifndef RE_PROJECTEXPLORER_HPP
#define RE_PROJECTEXPLORER_HPP

#include "rwxComponent.hpp"

#include <wx/wx.h>
#include <wx/dataview.h>

class reProjectExplorer : public wxDataViewTreeCtrl{
public:
	reProjectExplorer(rwxComponent* component, wxWindow* parent, wxWindowID id = wxID_ANY);

private:
	rwxComponent* m_component;
};

#endif