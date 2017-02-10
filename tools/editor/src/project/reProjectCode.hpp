#pragma once

#include <wx/filename.h>

#include "xml/rXMLDocument.hpp"

#include "rEngine.hpp"

class reProjectCode {
public:
	reProjectCode(rEngine* component);

public:
	void SetBasePath(const wxString& path);
	void CreateProject(const wxString& projectName);

	bool CreateBehavior(const wxString& className);
	const wxArrayString& GetBehaviorClasses() const;

public:
	void Save(rXMLDocument& document);
	void Load(rXMLDocument& document);

private:
	void EnsureAssetDir(const wxString& dirName);

	void CopyTemplate(const wxString& templateName, const wxString& dir = wxEmptyString);
	bool FillTemplate(const wxString& templateSrc, const wxString& search, const wxString& replace);

private:
	rEngine* _engine;
	wxFileName m_codeDir;

	wxArrayString _behaviors;
};