#pragma once

#include "rwxComponent.hpp"
#include "asset/rModel.hpp"

#include <wx/filename.h>

class reProjectAssets {
public:
	reProjectAssets(rwxComponent* component);

public:
	recondite::Model* ImportModel(const wxString& path);

	void SetBasePath(const wxString& path);
	wxString GetDirectoryPath();

	wxString GetAssetPath(rAssetType assetType, const wxString& name);

private:
	void WriteModel(const recondite::ModelData& modelData, const wxString& name);

private:
	wxFileName m_assetsDir;
	rwxComponent* _component;
};