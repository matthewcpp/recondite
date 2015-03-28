#ifndef RE_PROPERTYINTERFACE_HPP
#define RE_PROPERTYINTERFACE_HPP

#include "rActor3.hpp"
#include "interface/riSerialization.hpp"

#include <wx/wx.h>
#include <wx/sstream.h>
#include <wx/txtstrm.h>

#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/property.h>
#include <wx/propgrid/advprops.h>

class rePropertyReader : public riSerializationTarget{
public:
	rePropertyReader(wxPropertyGrid* grid);

public:
	void Read(rActor3* actor);

public:
	virtual bool Boolean(const rString& name, bool& val) override;
	virtual bool Int(const rString& name, int& val) override;
	virtual bool Float(const rString& name, float& val) override;
	virtual bool String(const rString& name, rString& val) override;
	virtual bool Vector3(const rString& name, rVector3& val) override;
	virtual bool Color(const rString& name, rColor& color) override;

	virtual bool Category(const rString& name) override;

	virtual riSerializationTarget* SubObject(const rString& name) override;
	virtual bool Next() override;

private:
	wxString DisplayName(const wxString& name);

private:
	wxPropertyGrid* m_grid;
};

#endif