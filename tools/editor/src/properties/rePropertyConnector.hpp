#ifndef RE_PROPERTYCONNECTOR_HPP
#define RE_PROPERTYCONNECTOR_HPP

#include <vector>

#include "rActor3.hpp"

#include <wx/wx.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/property.h>
#include <wx/propgrid/advprops.h>

typedef std::vector<wxPGProperty*> rePGPropertyVector;

class rePropertyConnector{
public:
	virtual ~rePropertyConnector(){}
public:
	virtual void SetPGProperties(wxPropertyGrid* grid) = 0;
	virtual void RefreshPGProperties(wxPropertyGrid* grid) = 0;

	virtual bool SetBoolProperty(const wxString& name, bool val) { return false; }
	virtual bool SetDoubleProperty(const wxString& name, double val) { return false; }
	virtual bool SetIntProperty(const wxString& name, int val) { return false; }
	virtual bool SetColorProperty(const wxString& name, wxColor val) { return false; }
};

#endif