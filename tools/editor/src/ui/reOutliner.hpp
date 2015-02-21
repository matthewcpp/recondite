#ifndef RE_OUTLINER_HPP
#define RE_OUTLINER_HPP

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

	void OnActorAddedToScene(rEvent& event);
	void OnComponentInitialized(rEvent& event);

	void OnLevelBeginLoad(rEvent& event);
	void OnLevelEndLoad(rEvent& event);

private:
	reComponent* m_component;

	rePropertyInspector* m_propertyInspector;
};

#endif