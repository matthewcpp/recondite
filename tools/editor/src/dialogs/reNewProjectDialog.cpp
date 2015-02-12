#include "reNewProjectDialog.hpp"

reNewProjectDialog::reNewProjectDialog()
	:wxDialog(nullptr, wxID_ANY, "New Project")
{
	m_nameText = new wxTextCtrl(this, wxID_ANY);
	m_directoryPicker = new wxDirPickerCtrl(this, wxID_ANY, wxEmptyString, "Choose Project Directory");

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* flexSizer = new wxFlexGridSizer(2, 2, 3, 3);
	flexSizer->Add(new wxStaticText(this, wxID_ANY, "Project Name:"));
	flexSizer->Add(m_nameText);
	flexSizer->Add(new wxStaticText(this, wxID_ANY, "Project Directory:"));
	flexSizer->Add(m_directoryPicker);
	mainSizer->Add(flexSizer, 0, wxALL, 5);

	mainSizer->Add(CreateSeparatedButtonSizer(wxOK | wxCANCEL), 1, wxEXPAND| wxALL, 5);

	SetSizerAndFit(mainSizer);
}

wxString reNewProjectDialog::GetProjectName() const{
	return m_nameText->GetValue();
}

wxString reNewProjectDialog::GetProjectDir() const{
	return m_directoryPicker->GetPath();
}