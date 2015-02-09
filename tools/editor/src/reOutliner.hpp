#ifndef RE_OUTLINER_HPP
#define RE_OUTLINER_HPP

#include "rwxComponent.hpp"

#include <wx/wx.h>
#include <wx/dataview.h>

#include "rePropertyInspector.hpp"

class reOutliner : public wxDataViewTreeCtrl{
public:
	reOutliner(rwxComponent* component, rePropertyInspector* propertyInspector, wxWindow* parent, wxWindowID id = wxID_ANY);

	void UpdateLevel();

private:
	void OnItemSelected(wxDataViewEvent& event);

private:
	rwxComponent* m_component;

	rePropertyInspector* m_propertyInspector;
};

#endif