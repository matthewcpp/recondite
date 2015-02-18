#ifndef RE_OUTLINER_HPP
#define RE_OUTLINER_HPP

#include "rwxComponent.hpp"

#include <wx/wx.h>
#include <wx/dataview.h>

#include "rePropertyInspector.hpp"

#include "rEvents.hpp"

class reOutliner : public wxDataViewTreeCtrl{
public:
	reOutliner(rwxComponent* component, rePropertyInspector* propertyInspector, wxWindow* parent, wxWindowID id = wxID_ANY);

public:
	void OutlineLevel();

private:
	void OnItemSelected(wxDataViewEvent& event);

	void OnActorAddedToScene(rEvent& event);
	void OnComponentInitialized(rEvent& event);

	void OnLevelBeginLoad(rEvent& event);
	void OnLevelEndLoad(rEvent& event);

private:
	rwxComponent* m_component;

	rePropertyInspector* m_propertyInspector;
};

#endif