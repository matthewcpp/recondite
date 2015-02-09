#include "reOutliner.hpp"

reOutliner::reOutliner(rwxComponent* component, rePropertyInspector* propertyInspector, wxWindow* parent, wxWindowID id)
	:wxDataViewTreeCtrl(parent, id)
{
	m_component = component;
	m_propertyInspector = propertyInspector;

	Bind(wxEVT_DATAVIEW_SELECTION_CHANGED, &reOutliner::OnItemSelected, this);
}

void reOutliner::UpdateLevel(){
	rArrayString names;
	m_component->GetViewportNames(names);

	DeleteAllItems();

	wxDataViewItem levelRoot = AppendContainer(wxDataViewItem(0), "Level 1");
	AppendItem(levelRoot, "box01");
}

void reOutliner::OnItemSelected(wxDataViewEvent& event){
	wxString itemName = GetItemText(event.GetItem());
	m_propertyInspector->Inspect(itemName);
}