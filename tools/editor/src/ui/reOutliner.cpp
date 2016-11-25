#include "reOutliner.hpp"

reOutliner::reOutliner(reComponent* component, rePropertyInspector* propertyInspector, wxWindow* parent, wxWindowID id)
	:wxDataViewTreeCtrl(parent, id, wxDefaultPosition, wxDefaultSize, wxDV_MULTIPLE | wxDV_NO_HEADER)
{
	m_component = component;
	m_propertyInspector = propertyInspector;

	Bind(wxEVT_DATAVIEW_SELECTION_CHANGED, &reOutliner::OnItemSelected, this);
	Bind(wxEVT_DATAVIEW_ITEM_CONTEXT_MENU, &reOutliner::OnContext, this);

	Bind(wxEVT_DATAVIEW_ITEM_START_EDITING, &reOutliner::OnEditBegin, this);
	Bind(wxEVT_DATAVIEW_ITEM_VALUE_CHANGED, &reOutliner::OnItemEdit, this);
	
	m_component->Bind(rEVT_COMPONENT_INITIALIZED, this, &reOutliner::OnComponentInitialized);
}

void reOutliner::OnItemSelected(wxDataViewEvent& event){
	wxDataViewItem item = event.GetItem();

	if (item.IsOk()){
		wxString itemName = GetItemText(item);
		m_component->SelectionManager()->Select(itemName);
		m_component->GetViewportManager()->UpdateAllViewports();
	}
	else {
		event.Veto();
	}
}

void reOutliner::OnActorAddedToScene(rEvent& event){
	rActor3Event& actorEvent = static_cast<rActor3Event&> (event);

	rString actorId = actorEvent.Actor()->Id();

	wxDataViewItem item = AppendItem(wxDataViewItem(0), actorId.c_str());
	m_actorIdMap[actorId] = item;
}

void reOutliner::OnActorRemovedFromScene(rEvent& event){
	rActor3Event& actorEvent = static_cast<rActor3Event&> (event);

	rString actorId = actorEvent.Actor()->Id();

	if (m_actorIdMap.count(actorId)){
		DeleteItem(m_actorIdMap[actorId]);
		m_actorIdMap.erase(actorId);
	}
}

void reOutliner::OnActorRenamed(rEvent& event){
	rActor3RenameEvent& actorEvent = static_cast<rActor3RenameEvent&> (event);

	rString oldName = actorEvent.PreviousId();

	if (m_actorIdMap.count(oldName)){
		rActor3* actor = actorEvent.Actor();
		rString newName = actor->Id();
		wxDataViewItem item = m_actorIdMap[oldName];

		m_actorIdMap.erase(oldName);
		m_actorIdMap[newName] = item;
		SetItemText(item, newName.c_str());
	}
}

void reOutliner::OnComponentInitialized(rEvent& event){
	rScene* scene = m_component->GetScene();

	//bind scene events
	scene->Bind(rEVT_SCENE_ACTOR_ADDED, this, &reOutliner::OnActorAddedToScene);
	scene->Bind(rEVT_SCENE_ACTOR_REMOVED, this, &reOutliner::OnActorRemovedFromScene);
	scene->Bind(rEVT_SCENE_ACTOR_RENAMED, this, &reOutliner::OnActorRenamed);
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

void reOutliner::ClearOutliner() {
	DeleteAllItems();
	m_actorIdMap.clear();
}

void reOutliner::OutlineLevel(){
	rArrayString actorNames;
	m_component->GetScene()->GetActors(actorNames);

	for (auto& actorId : actorNames) {
		wxDataViewItem item = AppendItem(wxDataViewItem(0), actorId.c_str());
		m_actorIdMap[actorId] = item;
	}
}

void reOutliner::OnLevelBeginLoad(rEvent& event){
	ClearOutliner();
}

void reOutliner::OnLevelEndLoad(rEvent& event){
	OutlineLevel();
}

void reOutliner::OnContext(wxDataViewEvent& event){
	wxDataViewItem item = event.GetItem();
	
	if (item.IsOk()){
		wxMenu popupMenu;
		popupMenu.Append(0, "Delete");
		popupMenu.Append(1, "Rename...");

		int id = GetPopupMenuSelectionFromUser(popupMenu);

		if (id == 0){
			const wxArrayString& selection = m_component->SelectionManager()->GetSelection();
			m_component->SubmitCommand(new reDeleteActorCommand(selection, m_component));
		}
		else if (id == 1){
			wxString actorName = GetItemText(item);
			wxTextEntryDialog dialog(nullptr, "Name:", "Rename " + actorName);

			if (dialog.ShowModal() == wxID_OK){
				wxString newName = dialog.GetValue();
				DoActorRename(actorName, newName);
			}
		}
	}
}

void reOutliner::OnEditBegin(wxDataViewEvent& event){
	wxDataViewItem item = event.GetItem();
	m_CurrentEditedItem = GetItemText(item);
}

void reOutliner::OnItemEdit(wxDataViewEvent& event){
	if (m_CurrentEditedItem != wxEmptyString){
		wxString oldName = m_CurrentEditedItem;
		m_CurrentEditedItem.Clear();

		wxDataViewItem item = event.GetItem();
		wxString newName = GetItemText(item);

		bool result = DoActorRename(oldName, newName);

		if (!result)
			SetItemText(item, oldName);
	}
}

bool reOutliner::DoActorRename(const wxString& oldName, const wxString& newName){
	bool result = m_component->SubmitCommand(new reRenameActorCommand(oldName, newName, m_component));

	if (!result)
		wxMessageBox("This scene already contains an Actor named " + newName, "Unable to rename " + oldName, wxOK | wxCENTRE | wxICON_ERROR);
	
	return result;
}