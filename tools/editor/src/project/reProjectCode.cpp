#include "reProjectCode.hpp"

#include <wx/ffile.h>
#include <wx/filefn.h>

reProjectCode::reProjectCode(rEngine* engine) {
	_engine = engine;
}

void reProjectCode::SetBasePath(const wxString& path) {
	m_codeDir.SetPath(path);
	EnsureAssetDir("src");
	m_codeDir.AppendDir("src");
}

void reProjectCode::EnsureAssetDir(const wxString& dirName) {
	wxFileName codeDir(m_codeDir);
	codeDir.AppendDir(dirName);

	if (!codeDir.Exists()) {
		wxMkDir(codeDir.GetPath(), wxS_DIR_DEFAULT);
	}
}

void reProjectCode::CopyTemplate(const wxString& templateName, const wxString& dir) {
	wxFileName dest(m_codeDir);

	if (!dir.empty()) {
		dest.AppendDir(dir);

		if (!dest.Exists()) {
			wxMkDir(dest.GetPath(), wxS_DIR_DEFAULT);
		}
	}

	dest.SetFullName(templateName);
	wxCopyFile("templates/" + templateName, dest.GetFullPath());
}

void reProjectCode::CreateProject(const wxString& projectName) {
	CopyTemplate("Game.Private.hpp");
	CopyTemplate("Game.Private.cpp");
	CopyTemplate("Game.inl");
	FillTemplate("Application.cpp", "__GAME_NAME__", projectName);

	FillTemplate("CMakeLists.txt", "__GAME_NAME__", projectName);
	CopyTemplate("Game.inl", "cmake");
}

bool reProjectCode::FillTemplate(const wxString& templateName, const wxString& search, const wxString& replace) {
	wxString templateSrc = "templates/" + templateName;
	wxFFile templateFile(templateSrc);

	wxString str;
	templateFile.ReadAll(&str);

	str.Replace(search, replace);

	wxFileName dest(m_codeDir);
	dest.SetFullName(templateName);

	wxFFile destFile(dest.GetFullPath(), "w");
	destFile.Write(str);

	return true;
}

recondite::Behavior* CreateEditorBehavior() {
	return new recondite::Behavior();
}

bool reProjectCode::CreateBehavior(const wxString& className) {
	bool result = _engine->behaviors->DefineBehavior(className.c_str().AsChar(), &CreateEditorBehavior);

	if (result) {
		_behaviors.push_back(className);
	}

	return result;
}

const wxArrayString& reProjectCode::GetBehaviorClasses() const {
	return _behaviors;
}

void reProjectCode::Save(rXMLDocument& document) {
	rXMLElement* root = document.GetRoot();

	rXMLElement* code = root->CreateChild("code");
	rXMLElement* behaviors = code->CreateChild("behaviors");

	for (size_t i = 0; i < _behaviors.size(); i++) {
		behaviors->CreateChild<const char*>("behavior", _behaviors[i].c_str().AsChar());
	}
}

void reProjectCode::Load(rXMLDocument& document) {
	rXMLElement* code = document.GetRoot()->GetFirstChildNamed("code");
	if (!code) return;

	rXMLElement* behaviors = code->GetFirstChildNamed("behaviors");

	if (behaviors) {
		for (size_t i = 0; i < behaviors->NumChildren(); i++) {
			rXMLElement* behavior = behaviors->GetChild(i);

			rString name;
			behavior->GetText(name);

			CreateBehavior(name.c_str());
		}
	}
}