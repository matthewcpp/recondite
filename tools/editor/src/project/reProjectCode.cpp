#include "reProjectCode.hpp"

#include <wx/ffile.h>
#include <wx/filefn.h>

void reProjectCode::SetBasePath(const wxString& path) {
	m_codeDir.SetPath(path);
	EnsureAssetDir("src");
	m_codeDir.AppendDir("src");
}

void reProjectCode::EnsureAssetDir(const wxString& dirName) {
	wxFileName codeDir(m_codeDir);
	codeDir.AppendDir(dirName);

	if (!codeDir.Exists()) {
		wxMkDir(codeDir.GetPath(), wxS_DIR_DEFAULT);
	}
}

void reProjectCode::CopyTemplate(const wxString& templateName, const wxString& dir) {
	wxFileName dest(m_codeDir);

	if (!dir.empty()) {
		dest.AppendDir(dir);

		if (!dest.Exists()) {
			wxMkDir(dest.GetPath(), wxS_DIR_DEFAULT);
		}
	}

	dest.SetFullName(templateName);
	wxCopyFile("templates/" + templateName, dest.GetFullPath());
}

void reProjectCode::CreateProject(const wxString& projectName) {
	CopyTemplate("Game.Private.hpp");
	CopyTemplate("Game.Private.cpp");
	CopyTemplate("Game.inl");
	FillTemplate("Application.cpp", "__GAME_NAME__", projectName);

	FillTemplate("CMakeLists.txt", "__GAME_NAME__", projectName);
	CopyTemplate("Game.inl", "cmake");
}

bool reProjectCode::FillTemplate(const wxString& templateName, const wxString& search, const wxString& replace) {
	wxString templateSrc = "templates/" + templateName;
	wxFFile templateFile(templateSrc);

	wxString str;
	templateFile.ReadAll(&str);

	str.Replace(search, replace);

	wxFileName dest(m_codeDir);
	dest.SetFullName(templateName);

	wxFFile destFile(dest.GetFullPath(), "w");
	destFile.Write(str);

	return true;
}