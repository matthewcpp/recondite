#ifndef RE_PROJECTEXPLORER_HPP
#define RE_PROJECTEXPLORER_HPP

#include "project/reComponent.hpp"

#include <wx/wx.h>
#include <wx/dataview.h>

#include "reUIController.hpp"

#include "project/reProject.hpp"
#include "reModelViewer.hpp"

class reProjectExplorer : public wxDataViewTreeCtrl{
public:
	reProjectExplorer(reUIController* uiController, reModelViewerFrame* modelViewer, reComponent* component, wxWindow* parent, wxWindowID id = wxID_ANY);

	void ShowProject();
	void AddLevel(const wxString& name);
	void AddModel(const wxString& name);

private:
	void OnItemActivated(wxDataViewEvent& event);
	void OnContext(wxDataViewEvent& event);

	void ShowAssets(rAssetType assetType, wxDataViewItem parent);

private:
	enum reProjectExplorerId{
		reProjectExplorerRenameLevel = 6000,
		reProjectExplorerDeleteLevel,

		reProjectExplorerNewBehavior
	};

	void NewBehaviorContextMenu();
	void LevelContextMenu(wxDataViewItem target);
	void RenameLevel(wxDataViewItem target);
	void DeleteLevel(wxDataViewItem target);

private:
	reComponent* m_component;
	reModelViewerFrame* m_modelViewer;
	reUIController* m_uiController;

	wxDataViewItem m_projectRoot;
	wxDataViewItem m_levelsRoot;
	wxDataViewItem m_modelsRoot;
	wxDataViewItem m_behaviorRoot;
};

#endif