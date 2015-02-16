#include "reProjectExplorer.hpp"

reProjectExplorer::reProjectExplorer(rwxComponent* component, reProject* project, wxWindow* parent, wxWindowID id)
	:wxDataViewTreeCtrl(parent, id)
{
	m_component = component;
	m_project = project;

	Bind(wxEVT_DATAVIEW_ITEM_ACTIVATED, &reProjectExplorer::OnItemActivated, this);
}

void reProjectExplorer::ShowProject(){
	DeleteAllItems();

	m_projectRoot = AppendContainer(wxDataViewItem(0), m_project->Name());
	m_levelsRoot = AppendContainer(m_projectRoot, "Levels");
	Expand(m_projectRoot);

	const wxArrayString& levels = m_project->Levels();

	for (auto& level : levels){
		AppendItem(m_levelsRoot, level);
	}
}

void reProjectExplorer::AddLevel(const wxString& name){
	wxDataViewItem item = AppendItem(m_levelsRoot, name);
	Select(item);
	
}

void reProjectExplorer::OnItemActivated(wxDataViewEvent& event){
	wxDataViewItem target = event.GetItem();
	wxDataViewItem parent = GetModel()->GetParent(target);

	if (parent == m_levelsRoot){
		m_project->ActivateLevel(GetItemText(target));
	}
}