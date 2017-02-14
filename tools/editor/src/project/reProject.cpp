#include "reProject.hpp"

#include <wx/filefn.h> 
#include "stream/rOFileStream.hpp"
#include "stream/rIFileStream.hpp"

#include "primitive/rPrimitiveGrid.hpp"
#include "primitive/rPrimitiveBox.hpp"


reProject::reProject(rwxComponent* component){
	m_component = component;
	m_assets.reset(new reProjectAssets(m_component));
	m_code.reset(new reProjectCode(m_component->GetEngine()));
}

void reProject::Create(const wxString& directory, const wxString& name){
	Close();

	m_name = name;

	m_projectDir.AssignDir(directory);
	m_projectDir.AppendDir(name);
	m_assets->SetBasePath(m_projectDir.GetFullPath());
	m_code->SetBasePath(m_projectDir.GetFullPath());

	wxMkDir(m_projectDir.GetPath(), wxS_DIR_DEFAULT);
	wxMkDir(LevelDirPath(), wxS_DIR_DEFAULT);

	SaveProjectFile();

	m_code->CreateProject(m_name);
}

bool reProject::Open(const wxString& path){
	Close();

	wxFileName projPath(path);
	m_projectDir.AssignDir(projPath.GetPath());
	m_assets->SetBasePath(m_projectDir.GetFullPath());
	m_code->SetBasePath(m_projectDir.GetFullPath());

	rXMLDocument document;
	rIFileStream projectStream(path.c_str().AsChar());
	document.LoadFromStream(projectStream);

	rString textVal;
	document.GetRoot()->GetFirstChildNamed("name")->GetText(textVal);
	m_name = textVal.c_str();

	rXMLElement* levels = document.GetRoot()->GetFirstChildNamed("levels");

	for (size_t i = 0; i < levels->NumChildren(); i++) {
		levels->GetChild(i)->GetText(textVal);
		m_levels.push_back(textVal.c_str());
	}

	m_assets->Load(document);
	m_code->Load(document);

	return true;
}

void reProject::Close(){
	if (!IsOpen())
		return;

	SaveActiveLevel();
	SaveProjectFile();

	m_projectDir.Clear();
	m_name.Clear();
	m_levels.Clear();

	m_component->GetScene()->Clear();
}

void reProject::SaveProjectFile(){
	rXMLDocument document;
	rXMLElement* root = document.CreateRoot("project");
	root->CreateChild("name", m_name.c_str().AsChar());

	m_assets->Save(document);
	m_code->Save(document);

	rXMLElement* levels = root->CreateChild("levels");
	for (auto& levelname : m_levels) {
		levels->CreateChild("level", levelname.c_str().AsChar());
	}

	wxString projFile = ProjectFilePath();
	rOFileStream outStream(projFile.c_str().AsChar());
	document.WriteToStream(outStream);
}

wxString reProject::Directory() const{
	return m_projectDir.GetPath();
}

wxString reProject::Name() const{
	return m_name;
}

wxString reProject::ProjectFilePath() const{
	return m_projectDir.GetPathWithSep() + m_name + ".rprj";
}

wxString reProject::LevelDirPath() const{
	return m_projectDir.GetPathWithSep() + "levels";
}

bool reProject::IsOpen() const{
	return !m_name.IsEmpty();
}

const wxArrayString& reProject::Levels() const{
	return m_levels;
}

bool reProject::CheckForValidNewLevelName(const wxString& name){
	if (HasLevelNamed(name)){
		wxMessageBox("A level with that name already exists.", "Unable To Create New Level", wxOK | wxICON_ERROR);
		return false;
	}

	return true;
}

void reProject::CreateDefaultActors() {
	rEngine* engine = m_component->GetEngine();

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

bool reProject::CreateLevel(const wxString& name){
	if (!CheckForValidNewLevelName(name)) return false;

	m_levels.push_back(name);
	m_activeLevel = name;

	m_component->ClearScene();

	CreateDefaultActors();

	SaveActiveLevel();
	SaveProjectFile();

	return true;
}

bool reProject::RenameLevel(const wxString& oldName, const wxString& newName){
	if (!CheckForValidNewLevelName(newName)) return false;

	for (auto& level : m_levels){
		if (level == oldName){
			wxString oldLevelPath = LevelFilePath(oldName);
			wxString newLevelPath = LevelFilePath(newName);

			bool result = wxRenameFile(oldLevelPath, newLevelPath);
			if (result){
				level = newName;
				SaveProjectFile();
			}
			
			return result;
		}
	}

	return false;
}

bool reProject::DeleteLevel(const wxString& name){
	auto end = m_levels.end();
	for (auto it = m_levels.begin(); it != end; ++it){
		if (name == *it){
			wxString levelPath = LevelFilePath(name);
			bool result = wxRemoveFile(levelPath);

			if (result){
				m_levels.erase(it);
				SaveProjectFile();
				return true;
			}
		}
	}

	return false;
}

wxString reProject::LevelFilePath(const wxString& levelName) const{
	return LevelDirPath() + '/' + levelName + ".rlvl";
}

bool reProject::ActivateLevel(const wxString& name){
	CloseActiveLevel();

	m_activeLevel = name;
	wxString levelPath = LevelFilePath(m_activeLevel);

	m_component->LoadScene(levelPath.c_str().AsChar());

	return true;
}

wxString reProject::GetActiveLevel() {
	return m_activeLevel;
}

void reProject::CloseActiveLevel() {
	if (!m_activeLevel.empty()) {
		m_activeLevel.clear();
		m_component->ClearScene();
	}
}

void reProject::SaveActiveLevel(){
	if (!m_activeLevel.IsEmpty()){
		wxString levelPath = LevelFilePath(m_activeLevel);
		m_component->SaveScene(levelPath.c_str().AsChar());

		wxString assetFilePath = levelPath + ".assets";
		recondite::AssetManifest assetManifest;

		m_component->GetScene()->EachActor([&](rActor3* actor) {
			size_t assetCount = actor->GetNumAssets();
			rAssetType type;
			rString name;

			for (size_t i = 0; i < assetCount; i++) {
				actor->GetAsset(i, type, name);
				wxString assetPath = m_assets->GetAssetPath(type, name.c_str());

				assetManifest.Add(type, name, assetPath.c_str().AsChar());
			}
		});
		
		rOFileStream stream(assetFilePath.c_str().AsChar());
		assetManifest.Write(stream);
	}
}

bool reProject::HasLevelNamed(const wxString& name){
	for (auto& levelName : m_levels){
		if (levelName == name)
			return true;
	}

	return false;
}

reProjectAssets* reProject::Assets() {
	return m_assets.get();
}

reProjectCode* reProject::Code() {
	return m_code.get();
}