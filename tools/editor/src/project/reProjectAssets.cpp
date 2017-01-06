#include "reProjectAssets.hpp"

#include <wx/filename.h>

#include "ModelImporter.hpp"
#include "stream/rOFileStream.hpp"


reProjectAssets::reProjectAssets(rwxComponent* component) {
	_component = component;
}

void reProjectAssets::SetBasePath(const wxString& path) {
	m_assetsDir.SetPath(path);
	m_assetsDir.AppendDir("assets");

	if (!m_assetsDir.Exists()) {
		wxMkDir(m_assetsDir.GetPath(), wxS_DIR_DEFAULT);
	}
}

void reProjectAssets::WriteModel(const recondite::ModelData& modelData, const wxString& name) {
	wxFileName modelFile(m_assetsDir);
	modelFile.AppendDir("models");

	if (!modelFile.Exists()) {
		wxMkDir(modelFile.GetPath(), wxS_DIR_DEFAULT);
	}

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

		return model;
	}

	return nullptr;
}

wxString reProjectAssets::GetDirectoryPath() {
	return m_assetsDir.GetPathWithSep();
}

wxString reProjectAssets::GetAssetPath(rAssetType assetType, const wxString& name) {
	return "models/" + name + ".rmdl";
}