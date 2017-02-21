#include "reProjectCode.hpp"

#include "reUtils.hpp"

#include <wx/ffile.h>
#include <wx/filefn.h>
#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include <wx/sstream.h>

reProjectCode::reProjectCode(rEngine* engine) {
	_engine = engine;
}

void reProjectCode::SetBasePath(const wxString& path) {
	m_codeDir.SetPath(path);
	EnsureAssetDir("src");
	m_codeDir.AppendDir("src");
}

wxString reProjectCode::GetCodeDirectory() const {
	return m_codeDir.GetPathWithSep();
}

void reProjectCode::EnsureAssetDir(const wxString& dirName) {
	wxFileName codeDir(m_codeDir);
	codeDir.AppendDir(dirName);

	if (!codeDir.Exists()) {
		wxMkDir(codeDir.GetPath(), wxS_DIR_DEFAULT);
	}
}

void reProjectCode::CreateProject(const wxString& projectName) {
	bool result = reUtils::RecursiveCopy("assets/project_template", m_codeDir.GetFullPath());
	_projectName = projectName;

	GenerateGameBaseFile();
	GenerateBehaviorsCmakeList();

	reUtils::ReplaceInFile(m_codeDir.GetPathWithSep() + "CMakeLists.txt", "__GAME_NAME__", _projectName);
	reUtils::ReplaceInFile(m_codeDir.GetPathWithSep() + "src/CMakeLists.txt", "__GAME_NAME__", _projectName);
	reUtils::ReplaceInFile(m_codeDir.GetPathWithSep() + "src/Private/CMakeLists.txt", "__GAME_NAME__", _projectName);
}


recondite::Behavior* CreateEditorBehavior() {
	return new recondite::Behavior();
}

bool reProjectCode::CreateBehavior(const wxString& className, bool regenerateFiles) {
	bool result = _engine->behaviors->DefineBehavior(className.c_str().AsChar(), &CreateEditorBehavior);

	if (result) {
		_behaviors.push_back(className);

		wxFileName srcFile("assets/code_templates/Behavior.hpp");
		wxFileName destFile(m_codeDir.GetPathWithSep() + "src/Behaviors/" + className + ".hpp");
		reUtils::CopyAndReplaceInFile(srcFile.GetFullPath(), destFile.GetFullPath(), "__NAME__", className);

		srcFile.SetExt("cpp");
		destFile.SetExt("cpp");
		reUtils::CopyAndReplaceInFile(srcFile.GetFullPath(), destFile.GetFullPath(), "__NAME__", className);

		if (regenerateFiles) {
			GenerateGameBaseFile();
			GenerateBehaviorsCmakeList();
		}
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

	rString nameStr;
	rXMLElement* projectNameNode = document.GetRoot()->GetFirstChildNamed("name");
	projectNameNode->GetText(nameStr);
	_projectName = nameStr.c_str();

	rXMLElement* behaviors = code->GetFirstChildNamed("behaviors");

	if (behaviors) {
		for (size_t i = 0; i < behaviors->NumChildren(); i++) {
			rXMLElement* behavior = behaviors->GetChild(i);
			behavior->GetText(nameStr);

			CreateBehavior(nameStr.c_str(), false);
		}
	}
}

void reProjectCode::UpdateCodeFiles() {
	GenerateGameBaseFile();
}


void reProjectCode::GenerateGameBaseFile() {
	wxStringOutputStream includeData, defineData;
	wxTextOutputStream includeFileStream(includeData), defineStatementStream(defineData);

	for (size_t i = 0; i < _behaviors.size(); i++) {
		includeFileStream << "#include \"Behaviors/" << _behaviors[i] << ".hpp\"" <<endl;
		defineStatementStream << '\t' << "engine->behaviors->DefineBehavior(\"" << _behaviors[i] << "\", &__CreateBehavior<" << _behaviors[i] << ">);" << endl;
	}

	wxArrayString search, replace;
	search.push_back("//#<<BEHAVIOR_INCLUDES>>"); replace.push_back(includeData.GetString());
	search.push_back("//#<<BEHAVIOR_DEFINES>>"); replace.push_back(defineData.GetString());

	reUtils::CopyAndReplaceInFile("assets/code_templates/GameBase.Private.cpp", m_codeDir.GetPathWithSep() + "src/Private/GameBase.Private.cpp", search, replace);
}

void reProjectCode::GenerateBehaviorsCmakeList() {
	wxStringOutputStream fileListData;
	wxTextOutputStream fileListStream(fileListData);

	for (size_t i = 0; i < _behaviors.size(); i++) {
		fileListStream << "list(APPEND behavior_files ${CMAKE_CURRENT_LIST_DIR}/" << _behaviors[i] << ".hpp)" << endl;
		fileListStream << "list(APPEND behavior_files ${CMAKE_CURRENT_LIST_DIR}/" << _behaviors[i] << ".cpp)" << endl;
	}

	wxArrayString search, replace;
	search.push_back("#<<BEHAVIOR_FILES>>");  replace.push_back(fileListData.GetString());
	search.push_back("__GAME_NAME__"); replace.push_back(_projectName);

	reUtils::CopyAndReplaceInFile("assets/code_templates/Behaviors.CmakeLists.txt", m_codeDir.GetPathWithSep() + "src/Behaviors/CMakeLists.txt", search, replace);
}
