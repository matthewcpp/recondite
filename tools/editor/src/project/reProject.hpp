#ifndef RE_PROJECT_HPP
#define RE_PROJECT_HPP

#include <memory>

#include "rwxComponent.hpp"

#include <wx/wx.h>
#include <wx/filename.h>

#include "reProjectAssets.hpp"

class reProject{
public:
	reProject(rwxComponent* component);

	void Create(const wxString& directory, const wxString& name);
	void Close();
	bool Open(const wxString& path);

	void SaveProjectFile();

	bool CreateLevel(const wxString& name);
	bool RenameLevel(const wxString& oldName, const wxString& newName);
	bool DeleteLevel(const wxString& name);
	bool ActivateLevel(const wxString& name);
	void SaveActiveLevel();
	wxString GetActiveLevel();
	void CloseActiveLevel();
	bool HasLevelNamed(const wxString& name);

	wxString Directory() const;
	wxString Name() const;
	wxString ProjectFilePath() const;
	wxString LevelDirPath() const;
	wxString LevelFilePath(const wxString& levelName) const;

	bool IsOpen() const;

	const wxArrayString& Levels() const;

	reProjectAssets* Assets();

private:
	bool CheckForValidNewLevelName(const wxString& name);
	void CreateDefaultActors();

private:
	wxFileName m_projectDir;
	wxString m_name;

	rwxComponent* m_component;

	wxArrayString m_levels;
	wxString m_activeLevel;

	std::unique_ptr<reProjectAssets> m_assets;

	rNO_COPY_CLASS(reProject);
};

#endif