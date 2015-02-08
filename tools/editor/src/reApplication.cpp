#include "reApplication.hpp"

bool reApplication::OnInit(){
	m_rwxComponent = new rwxComponent();

	reMainFrame* mainFrame = new reMainFrame(m_rwxComponent, "Recondite Editor", wxDefaultPosition, wxSize(1024, 768));
	mainFrame->Show(true);
	return true;
}

wxIMPLEMENT_APP(reApplication);