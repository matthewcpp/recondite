#include "reProjectBuilder.hpp"

#include <wx/thread.h>
#include <wx/process.h>
#include <wx/progdlg.h>
#include <wx/utils.h> 

class reBundleAssetThread : public wxThread {
public:
	reBundleAssetThread(reComponent* component, reProjectBuilder* builder);
	virtual ExitCode Entry();

private:
	reComponent* _component;
	reProjectBuilder* _builder;
};

reBundleAssetThread::reBundleAssetThread(reComponent* component, reProjectBuilder* builder) {
	_component = component;
	_builder = builder;
}

wxThread::ExitCode reBundleAssetThread::Entry() {
	_component->GetProject()->BundleAssets();

	_builder->AssetBundleComplete();
	return (wxThread::ExitCode)0;
}

//--------------------------

class reConfigureProcess : public wxProcess{
public:
	reConfigureProcess(reProjectBuilder* builder);

public:
	virtual void OnTerminate(int pid, int status) override;

private:
	reProjectBuilder* _builder;
};

reConfigureProcess::reConfigureProcess(reProjectBuilder* builder)
	:wxProcess(wxPROCESS_DEFAULT) {
	_builder = builder;
}

void reConfigureProcess::OnTerminate(int pid, int status) {
	_builder->ConfigurationComplete();
}

//--------------------------

class reBuildProcess : public wxProcess {
public:
	reBuildProcess(reProjectBuilder* builder);

public:
	virtual void OnTerminate(int pid, int status) override;

private:
	reProjectBuilder* _builder;
};

reBuildProcess::reBuildProcess(reProjectBuilder* builder)
	:wxProcess(wxPROCESS_DEFAULT) {
	_builder = builder;
}

void reBuildProcess::OnTerminate(int pid, int status) {
	_builder->DoneBuilding();
}

//--------------------------

reProjectBuilder::reProjectBuilder(reComponent* component) {
	_component = component;

	_assetsBundled = false;
	_isBuilding = false;
	_run = false;
	_open = false;
}

bool reProjectBuilder::Configure() {
	if (!IsBuilding()) {
		_open = true;
		ConfigureProject();

		return true;
	}
	else {
		return false;
	}
}

bool reProjectBuilder::Build() {
	if (!IsBuilding()) {
		_isBuilding = true;
		_run = false;

		BundleAssets();
		ConfigureProject();

		return true;
	}
	else {
		return false;
	}
}

bool reProjectBuilder::BuildAndRun(const wxString& level) {
	if (!IsBuilding()) {
		_isBuilding = true;
		_run = true;
		_level = level;

		BundleAssets();
		ConfigureProject();

		return true;
	}
	else {
		return false;
	}

}

void reProjectBuilder::BundleAssets() {
	reBundleAssetThread* assetbundleThread = new reBundleAssetThread(_component, this);
	assetbundleThread->Run();

	while (!_assetsBundled) {
		wxThread::This()->Sleep(1);
	}
}

void reProjectBuilder::ConfigureProject() {
	wxString configureCommand = _component->GetProject()->ProjectScriptPath() + " configure";
	wxProcess* configureProcess = new reConfigureProcess(this);

	wxExecute(configureCommand, wxEXEC_ASYNC, configureProcess);
}

void reProjectBuilder::AssetBundleComplete() {
	_assetsBundled = true;
}

void reProjectBuilder::ConfigurationComplete() {
	if (_open) {
		_open = false;
		wxString openCommand = _component->GetProject()->ProjectScriptPath() + " edit";
		wxExecute(openCommand, wxEXEC_ASYNC);
	}
	else {
		wxString buildCommand = _component->GetProject()->ProjectScriptPath() + " build";
		wxProcess* buildProcess = new reBuildProcess(this);

		wxExecute(buildCommand, wxEXEC_ASYNC, buildProcess);
	}
}

bool reProjectBuilder::IsBuilding() const {
	return _isBuilding;
}

void reProjectBuilder::DoneBuilding() {
	if (_run) {
		wxString buildCommand = _component->GetProject()->ProjectScriptPath() + " debug " + _level;
		wxExecute(buildCommand, wxEXEC_ASYNC);
		_run = false;
	}

	_isBuilding = false;
}

bool reProjectBuilder::Open() {
	if (IsBuilt()) {
		wxString buildCommand = _component->GetProject()->ProjectScriptPath() + " edit";
		wxExecute(buildCommand, wxEXEC_ASYNC);
	}
	else {
		_open = true;
		Configure();
	}


	return true;
}

bool reProjectBuilder::IsBuilt() {
	wxFileName codeDir = _component->GetProject()->Code()->GetCodeDirectory();
	codeDir.AppendDir("build");

	return codeDir.Exists();
}