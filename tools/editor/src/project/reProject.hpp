#ifndef RE_PROJECT_HPP
#define RE_PROJECT_HPP

#include <wx/wx.h>
#include <wx/filename.h>
#include <wx/filefn.h> 
#include <wx/xml/xml.h>

class reProject{
public:
	void Create(const wxString& directory, const wxString& name);
	void Close();
	bool Open(const wxString& path);

	void SaveProjectFile();

	wxString Directory() const;
	wxString Name() const;
	wxString ProjectFilePath() const;

	bool IsOpen() const;

private:
	wxFileName m_projectDir;
	wxString m_name;
};

#endif