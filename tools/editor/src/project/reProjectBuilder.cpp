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
}

bool reProjectBuilder::BuildAndRun() {
	if (!IsBuilding()) {
		_isBuilding = true;
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

	//wxMessageBox("project Configured!");
}

void reProjectBuilder::AssetBundleComplete() {
	_assetsBundled = true;
}

void reProjectBuilder::ConfigurationComplete() {
	wxString buildCommand = _component->GetProject()->ProjectScriptPath() + " build";
	wxProcess* buildProcess = new reBuildProcess(this);

	wxExecute(buildCommand, wxEXEC_ASYNC, buildProcess);
}

bool reProjectBuilder::IsBuilding() const {
	return _isBuilding;
}

void reProjectBuilder::DoneBuilding() {
	wxString buildCommand = _component->GetProject()->ProjectScriptPath() + " debug";
	wxExecute(buildCommand, wxEXEC_ASYNC);

	_isBuilding = false;
}
