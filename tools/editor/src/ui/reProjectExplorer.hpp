#ifndef RE_PROJECTEXPLORER_HPP
#define RE_PROJECTEXPLORER_HPP

#include "rwxComponent.hpp"

#include <wx/wx.h>
#include <wx/dataview.h>

#include "project/reProject.hpp"

class reProjectExplorer : public wxDataViewTreeCtrl{
public:
	reProjectExplorer(rwxComponent* component, reProject* project, wxWindow* parent, wxWindowID id = wxID_ANY);

	void ShowProject();

private:
	rwxComponent* m_component;
	reProject* m_project;

	wxDataViewItem m_projectRoot;
	wxDataViewItem m_levelsRoot;
};

#endif