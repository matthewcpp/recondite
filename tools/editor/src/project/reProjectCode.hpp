#pragma once

#include <wx/filename.h>

class reProjectCode {
public:
	void SetBasePath(const wxString& path);
	void CreateProject(const wxString& projectName);

	
private:
	void EnsureAssetDir(const wxString& dirName);

	void CopyTemplate(const wxString& templateName, const wxString& dir = wxEmptyString);
	bool FillTemplate(const wxString& templateSrc, const wxString& search, const wxString& replace);

private:
	wxFileName m_codeDir;
};