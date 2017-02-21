#include "reProjectAssets.hpp"

#include <map>
#include <set>

#include <wx/filename.h>
#include <wx/filefn.h>

#include "ModelImporter.hpp"
#include "stream/rOFileStream.hpp"

#include "rResourceEvent.hpp"

#include "rPath.hpp"


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
		WriteModel(modelData, modelName);

		if (modelData.GetLineMeshCount() == 0) {
			CreateSelectionWireframeForModel(modelData);
		}

		recondite::Model* model = _component->GetEngine()->content->Models()->LoadFromData(modelData, modelName.c_str().AsChar());

		wxString modelHandle = GetAssetPath(rAssetType::Model, modelName);
		_manifest.Add(rAssetType::Model, modelName.c_str().AsChar(), modelHandle.c_str().AsChar());

		return model;
	}

	return nullptr;
}

void reProjectAssets::OnModelResourceLoaded(rEvent& event) {
	rResourceLoadedEvent& resourceLoadedEvent = (rResourceLoadedEvent&)event;
	ModelData* modelData = resourceLoadedEvent.GetModelData();

	if (modelData->GetLineMeshCount() == 0) {
		CreateSelectionWireframeForModel(*modelData);
	}
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



void reProjectAssets::CreateSelectionWireframeForModel(recondite::ModelData& modelData) {
	//temp implementation?
	std::map<uint16_t, std::set<uint16_t>> lineSegmentMap;

	//generate a wireframe representation
	for (size_t m = 0; m < modelData.GetTriangleMeshCount(); m++) {
		recondite::MeshData* meshData = modelData.GetTriangleMesh(m);

		for (size_t i = 0; i < meshData->GetElementCount(); i+=3) {
			uint16_t p0 = meshData->GetElement(i);
			uint16_t p1 = meshData->GetElement(i+1);
			uint16_t p2 = meshData->GetElement(i+2);

			if (p0 < p1)  lineSegmentMap[p0].insert(p1); else  lineSegmentMap[p1].insert(p0);
			if (p1 < p2)  lineSegmentMap[p1].insert(p2); else  lineSegmentMap[p2].insert(p1);
			if (p2 < p0)  lineSegmentMap[p2].insert(p0); else  lineSegmentMap[p0].insert(p2);
		}
	}

	//create a new line mesh and add generated wireframe
	uint32_t newMaterialId = modelData.CreateMaterial()->id;
	recondite::MeshData* lineMesh = modelData.CreateLineMesh();
	lineMesh->SetMaterialDataId(newMaterialId);

	for (auto& entry : lineSegmentMap) {
		for (auto element : entry.second) {
			lineMesh->Push(entry.first, element);
		}
	}
}

void reProjectAssets::Init() {
	_component->GetEngine()->content->Events()->Bind(rEVT_MODEL_RESOURCE_LOADED, this, &reProjectAssets::OnModelResourceLoaded);
}

bool reProjectAssets::BundleAssets(recondite::ArchiveData& archiveData) {
	riFileSystem* filesystem = _component->GetEngine()->filesystem;

	rString name, assetPath;
	size_t count, fileSize;

	count = _manifest.Count(rAssetType::Model);

	for (size_t i = 0; i < count; i++) {
		_manifest.Get(rAssetType::Model, i, name, assetPath);
		rString absolutePath = rPath::Combine(m_assetsDir.GetFullPath().c_str().AsChar(), assetPath);

		if (filesystem->Exists(absolutePath)) {
			filesystem->FileSize(absolutePath, fileSize);
			archiveData.SetKeyFromFilePath(assetPath, absolutePath, fileSize);
		}
	}

	return true;
}