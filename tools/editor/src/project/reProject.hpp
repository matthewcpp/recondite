#ifndef RE_PROJECT_HPP
#define RE_PROJECT_HPP

#include <memory>

#include "rwxComponent.hpp"

#include <wx/wx.h>
#include <wx/filename.h>

#include "rDefs.hpp"

#include "reProjectAssets.hpp"
#include "reProjectCode.hpp"
#include "reProjectLevels.hpp"

class reProject{
public:
	reProject(rwxComponent* component);

	void Create(const wxString& directory, const wxString& name);
	void Close();
	bool Open(const wxString& path);

	void SaveProjectFile();

	wxString Directory() const;
	wxString Name() const;
	wxString ProjectFilePath() const;

	bool IsOpen() const;

	bool BundleAssets();

	reProjectLevels* Levels() const;
	reProjectAssets* Assets();
	reProjectCode* Code();

private:
	void SetBasePaths();

private:
	wxFileName m_projectDir;
	wxString m_name;

	rwxComponent* m_component;

	wxString m_activeLevel;

	std::unique_ptr<reProjectAssets> m_assets;
	std::unique_ptr<reProjectCode> m_code;
	std::unique_ptr<reProjectLevels> m_levels;

	rNO_COPY_CLASS(reProject);
};

#endif