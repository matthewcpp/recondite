#include "reApplication.hpp"

bool reApplication::OnInit(){
	reMainFrame* mainFrame = new reMainFrame("Recondite Editor", wxDefaultPosition, wxDefaultSize);
	mainFrame->Show(true);
	return true;
}

wxIMPLEMENT_APP(reApplication);