#include "reApplication.hpp"

bool reApplication::OnInit(){
	m_reComponent = new reComponent();

	wxInitAllImageHandlers();

	SetupPaths();

	reMainFrame* mainFrame = new reMainFrame(m_reComponent, "Recondite Editor");
	mainFrame->Show(true);
	mainFrame->Maximize();
	return true;
}

int reApplication::OnExit() {
	delete m_reComponent;

	return 0;
}

void reApplication::SetupPaths(){
	wxStandardPaths& standardPaths = wxStandardPaths::Get();
	wxString appPath = standardPaths.GetExecutablePath();

	wxFileName cwd(appPath);
	wxSetWorkingDirectory(cwd.GetPath());
}

wxIMPLEMENT_APP(reApplication);