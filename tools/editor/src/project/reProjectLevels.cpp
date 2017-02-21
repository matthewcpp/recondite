#include "reProjectLevels.hpp"

reProjectLevels::reProjectLevels(rwxComponent* component, reProjectAssets* projectAssets, reProjectCode* projectCode) {
	_component = component;
	_projectAssets = projectAssets;
	_projectCode = projectCode;
}

void reProjectLevels::SetBasePath(const wxString& path) {
	_levelsDir.SetPath(path);
	_levelsDir.AppendDir("levels");

	if (!_levelsDir.Exists()) {
		_levelsDir.Mkdir();
	}
}

wxString reProjectLevels::GetDirectoryPath() const {
	return _levelsDir.GetPathWithSep();
}

bool reProjectLevels::CreateLevel(const wxString& name) {
	if (HasLevelNamed(name)) return false;

	_levels.push_back(name);
	_activeLevel = name;

	_component->ClearScene();

	CreateDefaultActors();
	SaveActiveLevel();

	return true;
}

wxString reProjectLevels::AbsoluteLevelPath(const wxString& name) {
	return GetDirectoryPath() + name + ".rlvl";
}

bool reProjectLevels::RenameLevel(const wxString& oldName, const wxString& newName) {
	if (HasLevelNamed(newName)) return false;

	for (auto& level : _levels) {
		if (level == oldName) {
			wxString oldLevelPath = AbsoluteLevelPath(oldName);
			wxString newLevelPath = AbsoluteLevelPath(newName);

			bool result = wxRenameFile(oldLevelPath, newLevelPath);

			oldLevelPath += ".assets";
			newLevelPath += ".assets";
			wxRenameFile(oldLevelPath, newLevelPath);

			if (result) {
				level = newName;
			}

			return result;
		}
	}

	return false;
}

bool reProjectLevels::DeleteLevel(const wxString& name) {
	if (HasLevelNamed(name)) {
		auto end = _levels.end();
		for (auto it = _levels.begin(); it != end; ++it) {
			if (name == *it) {
				wxString filename = AbsoluteLevelPath(name);
				bool result = wxRemoveFile(filename);

				filename += ".assets";
				wxRemoveFile(filename);

				if (result) {
					_levels.erase(it);
					return true;
				}
			}
		}
	}

	return false;
}

#include "primitive/rPrimitiveGrid.hpp"
#include "primitive/rPrimitiveBox.hpp"

void reProjectLevels::CreateDefaultActors() {
	rEngine* engine = _component->GetEngine();

	rString groundPlaneId = engine->scene->GetDefaultActorId("PrimitivePlane");
	rPrimitiveGrid* groundPlane = new rPrimitiveGrid(groundPlaneId, engine);
	groundPlane->SetEdgeColor(rColor::Blue);
	groundPlane->SetWidth(100);
	groundPlane->SetDepth(100);

	rString boxId = engine->scene->GetDefaultActorId("PrimitiveBox");
	rPrimitiveBox* box = new rPrimitiveBox(boxId, engine);
	box->SetDepth(5);
	box->SetWidth(5);
	box->SetHeight(5);

	engine->scene->AddActor(groundPlane);
	engine->scene->AddActor(box);
}

void reProjectLevels::Save(rXMLDocument& document) {
	rXMLElement* levels = document.GetRoot()->CreateChild("levels");
	for (auto& levelname : _levels) {
		levels->CreateChild("level", levelname.c_str().AsChar());
	}
}

void reProjectLevels::Load(rXMLDocument& document) {
	rString textVal;
	rXMLElement* levels = document.GetRoot()->GetFirstChildNamed("levels");

	for (size_t i = 0; i < levels->NumChildren(); i++) {
		levels->GetChild(i)->GetText(textVal);
		_levels.push_back(textVal.c_str());
	}
}

void reProjectLevels::SaveActiveLevel() {
	if (!_activeLevel.IsEmpty()) {
		wxString levelPath = AbsoluteLevelPath(_activeLevel);
		_component->SaveScene(levelPath.c_str().AsChar());

		wxString assetFilePath = levelPath + ".assets";
		recondite::AssetManifest assetManifest;

		_component->GetScene()->EachActor([&](rActor3* actor) {
			size_t assetCount = actor->GetNumAssets();
			rAssetType type;
			rString name;

			for (size_t i = 0; i < assetCount; i++) {
				actor->GetAsset(i, type, name);
				wxString assetPath = _projectAssets->GetAssetPath(type, name.c_str());

				assetManifest.Add(type, name, assetPath.c_str().AsChar());
			}
		});

		auto levelAssetFile = _component->GetEngine()->filesystem->OpenWriteFileRef(assetFilePath.c_str().AsChar());
		assetManifest.Write(*levelAssetFile);
		_component->GetEngine()->filesystem->CloseWriteFileRef(levelAssetFile);
	}
}

wxString reProjectLevels::GetActiveLevel() {
	return _activeLevel;
}

void reProjectLevels::CloseActiveLevel() {
	if (!_activeLevel.empty()) {
		_activeLevel.clear();
		_component->ClearScene();
	}
}

bool reProjectLevels::ActivateLevel(const wxString& name) {
	if (HasLevelNamed(name)) {
		CloseActiveLevel();

		_activeLevel = name;
		wxString levelPath = AbsoluteLevelPath(_activeLevel);

		_component->LoadScene(levelPath.c_str().AsChar());

		return true;
	}
	else {
		return false;
	}
}

const wxArrayString& reProjectLevels::LevelNames() const {
	return _levels;
}

bool reProjectLevels::HasLevelNamed(const wxString& name) {
	return _levels.Index(name) != wxNOT_FOUND;
}

void reProjectLevels::BundleAssets(recondite::ArchiveData& archiveData) {
	rFileSystem* fileSystem = _component->GetEngine()->filesystem;
	size_t fileSize;

	for (auto& level : _levels) {
		rString absolutePath = AbsoluteLevelPath(level).c_str().AsChar();
		rString relativePath = ("levels/" + level + ".rlvl").c_str().AsChar();
		fileSystem->FileSize(absolutePath, fileSize);
		archiveData.SetKeyFromFilePath(relativePath, absolutePath, fileSize);

		absolutePath += ".assets";
		relativePath += ".assets";
		fileSystem->FileSize(absolutePath, fileSize);
		archiveData.SetKeyFromFilePath(relativePath, absolutePath, fileSize);
	}
}