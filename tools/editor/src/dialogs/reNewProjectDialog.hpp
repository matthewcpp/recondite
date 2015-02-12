#ifndef RE_NEWPROJECTDIALOG_HPP
#define RE_NEWPROJECTDIALOG_HPP

#include <wx/wx.h>
#include <wx/filepicker.h>

class reNewProjectDialog : public wxDialog{
public:
	reNewProjectDialog();
	wxString GetProjectName() const;
	wxString GetProjectDir() const;

private:
	wxTextCtrl* m_nameText;
	wxDirPickerCtrl* m_directoryPicker;
};

#endif