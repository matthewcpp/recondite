#include "reApplication.hpp"

bool reApplication::OnInit(){
	m_rwxComponent = new rwxComponent();

	reMainFrame* mainFrame = new reMainFrame(m_rwxComponent, "Recondite Editor");
	mainFrame->Show(true);
	mainFrame->Maximize();
	return true;
}

wxIMPLEMENT_APP(reApplication);