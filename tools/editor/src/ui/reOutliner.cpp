#include "reOutliner.hpp"

reOutliner::reOutliner(rwxComponent* component, rePropertyInspector* propertyInspector, wxWindow* parent, wxWindowID id)
	:wxDataViewTreeCtrl(parent, id)
{
	m_component = component;
	m_propertyInspector = propertyInspector;

	Bind(wxEVT_DATAVIEW_SELECTION_CHANGED, &reOutliner::OnItemSelected, this);

	m_component->Bind(rEVT_COMPONENT_INITIALIZED, this, &reOutliner::OnComponentInitialized);
}

void reOutliner::OnItemSelected(wxDataViewEvent& event){
	wxString itemName = GetItemText(event.GetItem());
	m_propertyInspector->Inspect(itemName);
}

void reOutliner::OnActorAddedToScene(rEvent& event){
	rActor3Event& actorEvent = static_cast<rActor3Event&> (event);
	AppendItem(wxDataViewItem(0), actorEvent.Actor()->Id().c_str());
}

void reOutliner::OnComponentInitialized(rEvent& event){
	rScene* scene = m_component->GetScene();

	scene->Bind(rEVT_SCENE_ACTOR_ADDED, this, &reOutliner::OnActorAddedToScene);
}

void reOutliner::OutlineLevel(){

}