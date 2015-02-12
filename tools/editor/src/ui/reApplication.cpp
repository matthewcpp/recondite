#include "reApplication.hpp"

bool reApplication::OnInit(){
	m_rwxComponent = new rwxComponent();
	m_project = new reProject();

	reMainFrame* mainFrame = new reMainFrame(m_rwxComponent, m_project, "Recondite Editor");
	mainFrame->Show(true);
	mainFrame->Maximize();
	return true;
}

int reApplication::OnExit(){
	delete m_project;

	return wxApp::OnExit();
}

wxIMPLEMENT_APP(reApplication);