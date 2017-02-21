#pragma once

#include "rwxComponent.hpp"

#include "reProjectAssets.hpp"
#include "reProjectCode.hpp"

#include <wx/wx.h>
#include <wx/filename.h>

#include "xml/rXMLDocument.hpp"

class reProjectLevels {
public:
	reProjectLevels(rwxComponent* component, reProjectAssets* projectAssets, reProjectCode* projectCode);

public:
	void SetBasePath(const wxString& path);
	bool CreateLevel(const wxString& name);
	bool RenameLevel(const wxString& oldName, const wxString& newName);
	bool DeleteLevel(const wxString& name);
	bool ActivateLevel(const wxString& name);
	void SaveActiveLevel();
	wxString GetActiveLevel();
	void CloseActiveLevel();
	bool HasLevelNamed(const wxString& name);

	wxString GetDirectoryPath() const;

	const wxArrayString& LevelNames() const;

public:
	void Save(rXMLDocument& document);
	void Load(rXMLDocument& document);

	void BundleAssets(recondite::ArchiveData& archiveData);

private:
	void CreateDefaultActors();
	wxString AbsoluteLevelPath(const wxString& name);

private:

	rwxComponent* _component;
	reProjectAssets* _projectAssets;
	reProjectCode* _projectCode;

	wxFileName _levelsDir;

	wxArrayString _levels;
	wxString _activeLevel;

};