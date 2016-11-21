#include "reProject.hpp"

#include "primitive/rPrimitiveGrid.hpp"
#include "primitive/rPrimitiveBox.hpp"

reProject::reProject(rwxComponent* component){
	m_component = component;
}

void reProject::Create(const wxString& directory, const wxString& name){
	Close();

	m_name = name;

	m_projectDir.AssignDir(directory);
	m_projectDir.AppendDir(name);

	wxMkDir(m_projectDir.GetPath(), wxS_DIR_DEFAULT);
	wxMkDir(LevelDirPath(), wxS_DIR_DEFAULT);

	SaveProjectFile();
}

bool reProject::Open(const wxString& path){
	Close();

	wxFileName projPath(path);
	m_projectDir.AssignDir(projPath.GetPath());

	wxXmlDocument doc(path);

	wxXmlNode* child = doc.GetRoot()->GetChildren();

	while (child){
		if (child->GetName() == "name") {
			m_name = child->GetNodeContent();
		}
		if (child->GetName() == "levels") {
			wxXmlNode* level = child->GetChildren();

			if (level){
				while (level){
					m_levels.push_back(level->GetNodeContent());
					level = level->GetNext();
				}
			}
		}

		child = child->GetNext();
	}

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
	wxXmlNode* root = new wxXmlNode(wxXML_ELEMENT_NODE, "project");
	wxXmlNode* nameElement = new wxXmlNode(root, wxXML_ELEMENT_NODE, "name");
	wxXmlNode* nameNode = new wxXmlNode(nameElement, wxXML_TEXT_NODE, "name", m_name);

	wxXmlNode* levelsElement = new wxXmlNode(root, wxXML_ELEMENT_NODE, "levels");
	for (auto& levelname : m_levels){
		wxXmlNode* levelElement = new wxXmlNode(levelsElement, wxXML_ELEMENT_NODE, "level");
		wxXmlNode* nameNode = new wxXmlNode(levelElement, wxXML_TEXT_NODE, "level", levelname);
	}

	wxXmlDocument document;
	document.SetRoot(root);

	wxString projFile = ProjectFilePath();
	document.Save(projFile);
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
	m_activeLevel = name;
	wxString levelPath = LevelFilePath(m_activeLevel);

	m_component->ClearScene();
	m_component->LoadScene(levelPath.c_str().AsChar());

	return true;
}

void reProject::SaveActiveLevel(){
	if (!m_activeLevel.IsEmpty()){
		wxString levelPath = LevelFilePath(m_activeLevel);
		m_component->SaveScene(levelPath.c_str().AsChar());
	}
}

bool reProject::HasLevelNamed(const wxString& name){
	for (auto& levelName : m_levels){
		if (levelName == name)
			return true;
	}

	return false;
}