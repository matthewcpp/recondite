#pragma once

#include "rwxComponent.hpp"
#include "asset/rModel.hpp"

#include <wx/filename.h>
#include "xml/rXMLDocument.hpp"
#include "asset/rAssetManifest.hpp"

class reProjectAssets {
public:
	reProjectAssets(rwxComponent* component);

public:
	recondite::Model* ImportModel(const wxString& path);
	bool DeleteModel(const wxString& name);

	void SetBasePath(const wxString& path);
	wxString GetDirectoryPath();

	wxString GetAssetPath(rAssetType assetType, const wxString& name);
	wxString GetAssetPreviewIcon(rAssetType assetType, const wxString& name);

	void Save(rXMLDocument& document);
	void Load(rXMLDocument& document);

	const recondite::AssetManifest* Manifest() const;

private:
	void WriteModel(const recondite::ModelData& modelData, const wxString& name);

private:
	wxFileName m_assetsDir;
	rwxComponent* _component;
	recondite::AssetManifest _manifest;
};