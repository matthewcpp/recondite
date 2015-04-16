#ifndef RE_OUTLINER_HPP
#define RE_OUTLINER_HPP

#include <map>

#include "project/reComponent.hpp"

#include <wx/wx.h>
#include <wx/dataview.h>

#include "rePropertyInspector.hpp"

#include "rEvents.hpp"

class reOutliner : public wxDataViewTreeCtrl{
public:
	reOutliner(reComponent* component, rePropertyInspector* propertyInspector, wxWindow* parent, wxWindowID id = wxID_ANY);

public:
	void OutlineLevel();

private:
	void OnItemSelected(wxDataViewEvent& event);
	void OnContext(wxDataViewEvent& event);
	void OnEditBegin(wxDataViewEvent& event);
	void OnItemEdit(wxDataViewEvent& event);

	void OnActorAddedToScene(rEvent& event);
	void OnActorRemovedFromScene(rEvent& event);
	void OnActorSelected(rEvent& event);
	void OnActorRenamed(rEvent& event);

	void OnComponentInitialized(rEvent& event);

	void OnLevelBeginLoad(rEvent& event);
	void OnLevelEndLoad(rEvent& event);

private:
	bool DoActorRename(const wxString& oldName, const wxString& newName);

private:
	reComponent* m_component;
	
	rePropertyInspector* m_propertyInspector;

	std::map<rString, wxDataViewItem> m_actorIdMap;

	wxString m_CurrentEditedItem;
};

#endif