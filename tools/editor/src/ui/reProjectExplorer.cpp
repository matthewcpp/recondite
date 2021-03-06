#include "reProjectExplorer.hpp"

reProjectExplorer::reProjectExplorer(reUIController* uiController, reModelViewerFrame* modelViewer, reComponent* component, wxWindow* parent, wxWindowID id)
	:wxDataViewTreeCtrl(parent, id)
{
	m_component = component;
	m_modelViewer = modelViewer;
	m_uiController = uiController;

	Bind(wxEVT_DATAVIEW_ITEM_ACTIVATED, &reProjectExplorer::OnItemActivated, this);
	Bind(wxEVT_DATAVIEW_ITEM_CONTEXT_MENU, &reProjectExplorer::OnContext, this);
}

void reProjectExplorer::ShowProject(){
	DeleteAllItems();

	m_projectRoot = AppendContainer(wxDataViewItem(0), m_component->GetProject()->Name());
	m_levelsRoot = AppendContainer(m_projectRoot, "Levels");
	wxDataViewItem assetContainer = AppendContainer(m_projectRoot, "Assets");
	m_modelsRoot = AppendContainer(assetContainer, "Models");
	m_behaviorRoot = AppendContainer(m_projectRoot, "Behaviors");

	Expand(m_projectRoot);

	const wxArrayString& levels = m_component->GetProject()->Levels()->LevelNames();

	for (auto& level : levels){
		AppendItem(m_levelsRoot, level);
	}

	const wxArrayString& behaviors = m_component->GetProject()->Code()->GetBehaviorClasses();

	for (auto& behavior : behaviors) {
		AppendItem(m_behaviorRoot, behavior);
	}

	ShowAssets(rAssetType::Model, m_modelsRoot);
}

void reProjectExplorer::AddLevel(const wxString& name){
	wxDataViewItem item = AppendItem(m_levelsRoot, name);
	Select(item);
}

void reProjectExplorer::AddModel(const wxString& name) {
	AppendItem(m_modelsRoot, name);
}

void reProjectExplorer::OnItemActivated(wxDataViewEvent& event){
	wxDataViewItem target = event.GetItem();
	wxDataViewItem parent = GetModel()->GetParent(target);

	if (parent == m_levelsRoot){
		bool result = m_uiController->ActivateLevel(GetItemText(target));

		if (!result) {
			event.Veto();
		}
	}
	else if (parent == m_modelsRoot) {
		wxString modelName = GetItemText(target);

		m_modelViewer->ViewModel(modelName);
	}
}

void reProjectExplorer::OnContext(wxDataViewEvent& event){
	wxDataViewItem target = event.GetItem();
	wxDataViewItem parent = GetModel()->GetParent(target);

	if (target == m_behaviorRoot) {
		NewBehaviorContextMenu();
	}
	else if (parent == m_levelsRoot){
		LevelContextMenu(target);
	}
}

void reProjectExplorer::NewBehaviorContextMenu() {
	wxMenu behaviorContextMenu;
	behaviorContextMenu.Append(reProjectExplorerNewBehavior, "New Behavior...");

	int selection = GetPopupMenuSelectionFromUser(behaviorContextMenu);

	if (selection == reProjectExplorerNewBehavior) {
		wxTextEntryDialog dialog(nullptr, "New Behavior Name:", "New Behavior", wxEmptyString);

		if (dialog.ShowModal() == wxID_OK) {
			wxString behaviorName = dialog.GetValue();

			if (!m_component->GetProject()->Code()->CreateBehavior(behaviorName)) {
				wxMessageBox("A behavior with that name already exists.");
			}
			else {
				AppendItem(m_behaviorRoot, behaviorName);
				m_component->GetProject()->SaveProjectFile();
			}
		}
	}
}

void reProjectExplorer::LevelContextMenu(wxDataViewItem target){
	wxMenu levelContextMenu;
	levelContextMenu.Append(reProjectExplorerRenameLevel, "Rename level...");
	levelContextMenu.Append(reProjectExplorerDeleteLevel, "Delete level...");

	int selection = GetPopupMenuSelectionFromUser(levelContextMenu);

	switch (selection){
		case reProjectExplorerRenameLevel:
			RenameLevel(target);
			break;

		case reProjectExplorerDeleteLevel:
			DeleteLevel(target);
			break;
	}
}

void reProjectExplorer::RenameLevel(wxDataViewItem target){
	wxString oldName = GetItemText(target);
	wxString newName = wxGetTextFromUser("Enter new name:", "Rename " + oldName);

	if (m_component->GetProject()->Levels()->RenameLevel(oldName, newName)){
		SetItemText(target, newName);
		m_component->GetProject()->SaveProjectFile();
	}
}

void reProjectExplorer::DeleteLevel(wxDataViewItem target){
	wxString levelName = GetItemText(target);

	int choice = wxMessageBox("Really delete " + levelName + "?", "Delete " + levelName, wxOK | wxCANCEL | wxICON_QUESTION | wxCENTRE);
	if (choice != wxOK) return;

	bool result = m_component->GetProject()->Levels()->DeleteLevel(levelName);
	if (result) {
		DeleteItem(target);
		m_component->GetProject()->SaveProjectFile();
	}
	
}

void reProjectExplorer::ShowAssets(rAssetType assetType, wxDataViewItem parent) {
	const recondite::AssetManifest* assets = m_component->GetProject()->Assets()->Manifest();

	size_t count = assets->Count(assetType);

	rString name, path;
	for (size_t i = 0; i < count; i++) {
		assets->Get(assetType, i, name, path);
		AppendItem(parent, name.c_str());
	}
}