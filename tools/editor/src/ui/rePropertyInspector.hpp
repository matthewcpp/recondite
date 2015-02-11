#ifndef RE_PROPERTYINSPECTOR_HPP
#define RE_PROPERTYINSPECTOR_HPP

#include "rwxComponent.hpp"

#include <wx/wx.h>
#include <wx/propgrid/propgrid.h>

#include "properties/rePropertyConnectors.hpp"

class rePropertyInspector : public wxPropertyGrid{
public:
	rePropertyInspector(rwxComponent* component, wxWindow* display, wxWindow* parent, wxWindowID id = wxID_ANY);

public:
	void Inspect(const wxString& actorName);

private:
	void OnPropertyValueChanged(wxPropertyGridEvent& event);

private:
	rwxComponent* m_component;
	wxWindow* m_display;

	rePropertyConnector* m_connector;
};

#endif