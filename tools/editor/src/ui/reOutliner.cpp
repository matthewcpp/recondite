#include "reOutliner.hpp"

reOutliner::reOutliner(reComponent* component, rePropertyInspector* propertyInspector, wxWindow* parent, wxWindowID id)
	:wxDataViewTreeCtrl(parent, id, wxDefaultPosition, wxDefaultSize, wxDV_MULTIPLE | wxDV_NO_HEADER)
{
	m_component = component;
	m_propertyInspector = propertyInspector;

	Bind(wxEVT_DATAVIEW_SELECTION_CHANGED, &reOutliner::OnItemSelected, this);
	Bind(wxEVT_DATAVIEW_ITEM_CONTEXT_MENU, &reOutliner::OnContext, this);
	
	m_component->Bind(rEVT_COMPONENT_INITIALIZED, this, &reOutliner::OnComponentInitialized);
}

void reOutliner::OnItemSelected(wxDataViewEvent& event){
	wxString itemName = GetItemText(event.GetItem());

	m_component->SelectionManager()->Select(itemName);
}

void reOutliner::OnActorAddedToScene(rEvent& event){
	rActor3Event& actorEvent = static_cast<rActor3Event&> (event);

	rString actorId = actorEvent.Actor()->Id();

	if (!m_component->IsReservedActor(actorId)){
		wxDataViewItem item = AppendItem(wxDataViewItem(0), actorId.c_str());
		m_actorIdMap[actorId] = item;
	}
}

void reOutliner::OnActorRemovedFromScene(rEvent& event){
	rActor3Event& actorEvent = static_cast<rActor3Event&> (event);

	rString actorId = actorEvent.Actor()->Id();

	if (m_actorIdMap.count(actorId)){
		DeleteItem(m_actorIdMap[actorId]);
		m_actorIdMap.erase(actorId);
	}
}

void reOutliner::OnComponentInitialized(rEvent& event){
	rScene* scene = m_component->GetScene();

	//bind scene events
	scene->Bind(rEVT_SCENE_ACTOR_ADDED, this, &reOutliner::OnActorAddedToScene);
	scene->Bind(rEVT_SCENE_ACTOR_REMOVED, this, &reOutliner::OnActorRemovedFromScene);

	scene->Bind(rEVT_SCENE_LOAD_BEGIN, this, &reOutliner::OnLevelBeginLoad);
	scene->Bind(rEVT_SCENE_LOAD_END, this, &reOutliner::OnLevelEndLoad);

	//bind selection events
	m_component->Bind(reSELECTION_SELECT, this, &reOutliner::OnActorSelected);
}

void reOutliner::OnActorSelected(rEvent& event){
	reSelectionEvent& selectionEvent = static_cast<reSelectionEvent&>(event);

	rString actorId = selectionEvent.Item().c_str().AsChar();

	if (m_actorIdMap.count(actorId)){
		UnselectAll();

		wxDataViewItem item = m_actorIdMap[actorId];
		Select(item);
	}
}

void reOutliner::OutlineLevel(){

}

void reOutliner::OnLevelBeginLoad(rEvent& event){
	DeleteAllItems();
	m_actorIdMap.clear();
}

void reOutliner::OnLevelEndLoad(rEvent& event){
	rArrayString actorNames;
	m_component->GetScene()->GetActors(actorNames);

	for (auto& actorId : actorNames){
		if (!m_component->IsReservedActor(actorId)){
			wxDataViewItem item = AppendItem(wxDataViewItem(0), actorId.c_str());
			m_actorIdMap[actorId] = item;
		}
	}
}

void reOutliner::OnContext(wxDataViewEvent& event){
	wxDataViewItem item = event.GetItem();
	
	if (item.IsOk()){
		wxMenu popupMenu;
		popupMenu.Append(0, "Delete");

		int id = GetPopupMenuSelectionFromUser(popupMenu);

		if (id == 0){
			const wxArrayString& selection = m_component->SelectionManager()->GetSelection();
			m_component->SubmitCommand(new reDeleteActorCommand(selection, m_component));
		}
	}
}