#include "reApplication.hpp"

bool reApplication::OnInit(){
	m_rwxComponent = new rwxComponent();
	m_project = new reProject(m_rwxComponent);

	wxInitAllImageHandlers();

	SetupPaths();

	reMainFrame* mainFrame = new reMainFrame(m_rwxComponent, m_project, "Recondite Editor");
	mainFrame->Show(true);
	mainFrame->Maximize();
	return true;
}

int reApplication::OnExit(){
	delete m_project;

	return wxApp::OnExit();
}

void reApplication::SetupPaths(){
	wxStandardPaths& standardPaths = wxStandardPaths::Get();
	wxString appPath = standardPaths.GetExecutablePath();

	wxFileName cwd(appPath);
	wxSetWorkingDirectory(cwd.GetPath());
}

wxIMPLEMENT_APP(reApplication);