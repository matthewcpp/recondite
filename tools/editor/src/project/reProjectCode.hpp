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

	bool CreateBehavior(const wxString& className, bool regenerateFiles = true);
	const wxArrayString& GetBehaviorClasses() const;

	bool CreateLevelBehavior(const wxString& levelName, bool regenerateFiles = true);
	bool DeleteLevelBehavior(const wxString& levelName);

	wxString GetCodeDirectory() const;

public:
	void Save(rXMLDocument& document);
	void Load(rXMLDocument& document);

private:
	void EnsureAssetDir(const wxString& dirName);
	void EnsureSrcDir(const wxString& dirname);

	bool DoCreateBehavior(const wxString& className, const wxString& destDir);

	void GenerateBehaviorsCmakeList();
	void GenerateLevelsCmakeList();
	void GenerateGameBaseFile();

private:
	wxString _projectName;
	rEngine* _engine;
	wxFileName m_codeDir;

	wxArrayString _behaviors;
	wxArrayString _levels;
};