#include "rePropertyInterface.hpp"

rePropertyReader::rePropertyReader(wxPropertyGrid* grid){
	m_grid = grid;
}

void rePropertyReader::Read(rActor3* actor){
	if (!actor) return;

	m_grid->Freeze();
	m_grid->Clear();
	actor->Save(this);
	m_grid->Thaw();
}

bool rePropertyReader::Boolean(const rString& name, bool& val) {
	wxString displayName = DisplayName(name.c_str());

	m_grid->Append(new wxBoolProperty(displayName, wxPG_LABEL, val));

	return true;
}

bool rePropertyReader::Int(const rString& name, int& val) {
	wxString displayName = DisplayName(name.c_str());

	m_grid->Append(new wxIntProperty(displayName, wxPG_LABEL, val));

	return true;
}

bool rePropertyReader::Float(const rString& name, float& val) {
	wxString displayName = DisplayName(name.c_str());

	m_grid->Append(new wxFloatProperty(displayName, wxPG_LABEL, val));

	return true;
}

bool rePropertyReader::String(const rString& name, rString& val) {
	wxString displayName = DisplayName(name.c_str());

	m_grid->Append(new wxStringProperty(displayName, wxPG_LABEL, val.c_str()));

	return true;
}

bool rePropertyReader::Vector3(const rString& name, rVector3& val) {
	wxString displayName = DisplayName(name.c_str());

	m_grid->Append(new wxFloatProperty(displayName + " X", wxPG_LABEL, val.x));
	m_grid->Append(new wxFloatProperty(displayName + " Y", wxPG_LABEL, val.y));
	m_grid->Append(new wxFloatProperty(displayName + " Z", wxPG_LABEL, val.z));

	return true;
}

bool rePropertyReader::Color(const rString& name, rColor& color) {
	wxString displayName = DisplayName(name.c_str());
	wxColor wxc(color.red, color.green, color.blue);

	m_grid->Append(new wxColourProperty(displayName, wxPG_LABEL, wxc));

	return true;
}

bool rePropertyReader::Category(const rString& name) {
	wxString displayName = DisplayName(name.c_str());

	m_grid->Append(new wxPropertyCategory(displayName, wxPG_LABEL));

	return true;
}

riSerializationTarget* rePropertyReader::SubObject(const rString& name) {
	return this;
}

bool rePropertyReader::Next(){
	return false;
}

wxString rePropertyReader::DisplayName(const wxString& name){
	wxString wxstr;
	wxStringOutputStream buffer(&wxstr);
	wxTextOutputStream str(buffer);

	for (size_t i = 0; i < name.length(); i++){
		wxUniChar c = name[i];
		if (i == 0) {
			str.PutChar(std::toupper(c));
		}
		else if (std::isupper(name[i])){
			str.PutChar(' ').PutChar(c);
		}
		else{
			str.PutChar(c);
		}
	}

	return wxstr;
}