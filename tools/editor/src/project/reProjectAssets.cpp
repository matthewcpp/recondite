#include "reProjectAssets.hpp"

#include <wx/filename.h>
#include <wx/filefn.h>

#include "ModelImporter.hpp"
#include "stream/rOFileStream.hpp"


reProjectAssets::reProjectAssets(rwxComponent* component) {
	_component = component;
}

void reProjectAssets::SetBasePath(const wxString& path) {
	m_assetsDir.SetPath(path);
	EnsureAssetDir("assets");
	m_assetsDir.AppendDir("assets");

	EnsureAssetDir("models");
	EnsureAssetDir("icons");
}

void reProjectAssets::EnsureAssetDir(const wxString& dirName) {
	wxFileName assetDir(m_assetsDir);
	assetDir.AppendDir(dirName);

	if (!assetDir.Exists()) {
		wxMkDir(assetDir.GetPath(), wxS_DIR_DEFAULT);
	}
}

void reProjectAssets::WriteModel(const recondite::ModelData& modelData, const wxString& name) {
	wxFileName modelFile(m_assetsDir);
	modelFile.AppendDir("models");

	modelFile.SetName(name);
	modelFile.SetExt("rmdl");

	rString outputFilePath = modelFile.GetFullPath().c_str().AsChar();
	rOFileStream outputStream(outputFilePath);

	modelData.Write(outputStream);
}

recondite::Model* reProjectAssets::ImportModel(const wxString& path) {
	import::ModelImporter modelImporter;
	import::ModelImporterOptions options;
	ModelData modelData;

	int error = modelImporter.ImportModel(path.c_str().AsChar(), modelData, options);

	if (!error) {
		modelData.CalculateBoundings();

		wxFileName modelPath(path);
		wxString modelName = modelPath.GetName();
		recondite::Model* model = _component->GetEngine()->content->Models()->LoadFromData(modelData, modelName.c_str().AsChar());

		WriteModel(modelData, modelName);

		wxString modelHandle = GetAssetPath(rAssetType::Model, modelName);
		_manifest.Add(rAssetType::Model, modelName.c_str().AsChar(), modelHandle.c_str().AsChar());

		return model;
	}

	return nullptr;
}

wxString reProjectAssets::GetDirectoryPath() {
	return m_assetsDir.GetPathWithSep();
}

wxString reProjectAssets::GetAssetPath(rAssetType assetType, const wxString& name) {
	//TODO: TEMP
	return "models/" + name + ".rmdl";
}

wxString reProjectAssets::GetAssetIconPath(rAssetType assetType, const wxString& name) {
	wxFileName previewFile(m_assetsDir);

	previewFile.AppendDir("icons");
	previewFile.SetName("model_" + name);
	previewFile.SetExt("png");

	return previewFile.GetFullPath();
}

void reProjectAssets::SetAssetIcon(const wxImage& image, rAssetType assetType, const wxString& name) {
	wxString iconPath = GetAssetIconPath(assetType, name);
	image.SaveFile(iconPath, wxBITMAP_TYPE_PNG);
}

void reProjectAssets::Save(rXMLDocument& document) {
	_manifest.Write(document);
}

void reProjectAssets::Load(rXMLDocument& document) {
	_manifest.Read(document);
}

const recondite::AssetManifest* reProjectAssets::Manifest() const{
	return &_manifest;
}

bool reProjectAssets::DeleteModel(const wxString& name) {
	if (_manifest.RemoveByName(rAssetType::Model, name.c_str().AsChar())) {
		_component->GetEngine()->content->Models()->Delete(name.c_str().AsChar());
		wxString assetPath = GetAssetPath(rAssetType::Model, name);

		wxString modelFile = GetDirectoryPath() + assetPath;
		wxRemoveFile(modelFile);
		return true;
	}

	return false;
}