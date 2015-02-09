#ifndef RE_PROPERTYINSPECTOR_HPP
#define RE_PROPERTYINSPECTOR_HPP

#include "rwxComponent.hpp"

#include <wx/wx.h>
#include <wx/propgrid/propgrid.h>

class rePropertyInspector : public wxPropertyGrid{
public:
	rePropertyInspector(rwxComponent* component, wxWindow* parent, wxWindowID id = wxID_ANY);

private:
	rwxComponent* m_component;
};

#endif