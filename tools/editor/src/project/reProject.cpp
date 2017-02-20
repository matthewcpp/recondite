#include "reProject.hpp"

#include <wx/filefn.h> 
#include "stream/rOFileStream.hpp"
#include "stream/rIFileStream.hpp"


reProject::reProject(rwxComponent* component){
	m_component = component;
	m_assets.reset(new reProjectAssets(m_component));
	m_code.reset(new reProjectCode(m_component->GetEngine()));
	m_levels.reset(new reProjectLevels(m_component, m_assets.get(), m_code.get()));
}

void reProject::Create(const wxString& directory, const wxString& name){
	Close();

	m_name = name;

	m_projectDir.AssignDir(directory);
	m_projectDir.AppendDir(name);

	if (!m_projectDir.Exists()) {
		m_projectDir.Mkdir();
	}

	SetBasePaths();
	m_code->CreateProject(m_name);

	SaveProjectFile();
}

void reProject::SetBasePaths() {
	wxString fullProjectPath = m_projectDir.GetFullPath();
	m_levels->SetBasePath(fullProjectPath);
	m_assets->SetBasePath(fullProjectPath);
	m_code->SetBasePath(fullProjectPath);
}

bool reProject::Open(const wxString& path){
	Close();

	wxFileName projPath(path);
	m_projectDir.AssignDir(projPath.GetPath());
	SetBasePaths();

	rXMLDocument document;
	rIFileStream projectStream(path.c_str().AsChar());
	document.LoadFromStream(projectStream);

	rString textVal;
	document.GetRoot()->GetFirstChildNamed("name")->GetText(textVal);
	m_name = textVal.c_str();

	m_levels->Load(document);
	m_assets->Load(document);
	m_code->Load(document);

	return true;
}

void reProject::Close(){
	if (!IsOpen())
		return;

	m_levels->SaveActiveLevel();
	SaveProjectFile();

	m_projectDir.Clear();
	m_name.Clear();

	m_component->GetScene()->Clear();
}

void reProject::SaveProjectFile(){
	rXMLDocument document;
	rXMLElement* root = document.CreateRoot("project");
	root->CreateChild("name", m_name.c_str().AsChar());

	m_levels->Save(document);
	m_assets->Save(document);
	m_code->Save(document);

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

bool reProject::IsOpen() const{
	return !m_name.IsEmpty();
}

reProjectLevels* reProject::Levels() const{
	return m_levels.get();
}

reProjectAssets* reProject::Assets() {
	return m_assets.get();
}

reProjectCode* reProject::Code() {
	return m_code.get();
}