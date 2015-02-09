#include "reMainFrame.hpp"

reMainFrame::reMainFrame(rwxComponent* component, const wxString& title, const wxPoint& pos, const wxSize& size)
	:wxFrame(NULL, wxID_ANY, title, pos, size)
{
	m_component = component;
	m_wxAuiManager.SetManagedWindow(this);

	m_viewportDisplay = new reViewportDisplay(m_component, this);
	m_propertyInspector = new rePropertyInspector(m_component, this);
	m_projectExplorer = new reProjectExplorer(m_component, this);
	m_outliner = new reOutliner(m_component, this);
	
	SetMenuBar(CreateEditorMenuBar());
	CreateStatusBar();

	m_wxAuiManager.AddPane(m_viewportDisplay, wxAuiPaneInfo()
		.Center()
		.Caption("Level View")
		.CloseButton(false));

	m_wxAuiManager.AddPane(m_propertyInspector, wxAuiPaneInfo()
		.Right()
		.Position(0)
		.Caption("Property Inspector")
		.Dockable(true)
		.Floatable(true)
		.MinimizeButton(true)
		.BestSize(250, 450));

	m_wxAuiManager.AddPane(m_projectExplorer, wxAuiPaneInfo()
		.Left()
		.Position(0)
		.Caption("Project Explorer")
		.Dockable(true)
		.Floatable(true)
		.MinimizeButton(true)
		.BestSize(250, 250));

	m_wxAuiManager.AddPane(m_outliner, wxAuiPaneInfo()
		.Left()
		.Position(1)
		.Caption("Outliner")
		.Dockable(true)
		.Floatable(true)
		.MinimizeButton(true)
		.BestSize(250, 450));

	m_wxAuiManager.Update();
}

reMainFrame::~reMainFrame(){
	m_wxAuiManager.UnInit();
}

wxMenuBar* reMainFrame::CreateEditorMenuBar(){
	wxMenuBar* menuBar = new wxMenuBar();

	wxMenu* fileMenu = new wxMenu();
	fileMenu->Append(reMainFramePopulate, "Populate");
	fileMenu->AppendSeparator();
	fileMenu->Append(wxID_EXIT, "Exit\tAlt+F4");
	menuBar->Append(fileMenu, "&File");

	wxMenu* viewMenu = new wxMenu();
	viewMenu->Append(reMainFrame_ViewPropertyInspector, "Property Inspector");
	viewMenu->Append(reMainFrame_ViewProjectExplorer, "Project Explorer");
	viewMenu->Append(reMainFrame_ViewProjectExplorer, "Outliner");
	menuBar->Append(viewMenu, "&View");

	Bind(wxEVT_MENU, &reMainFrame::OnFileExit, this, wxID_EXIT);
	Bind(wxEVT_MENU, &reMainFrame::OnViewWindowSelection, this, reMainFrame_IdUIBegin, reMainFrame_IdUIEnd);
	Bind(wxEVT_MENU, &reMainFrame::OnPopulate, this, reMainFramePopulate);

	return menuBar;
}

void reMainFrame::OnViewWindowSelection(wxCommandEvent& event){
	switch (event.GetId()){
		case reMainFrame_ViewPropertyInspector:
			m_wxAuiManager.GetPane(m_propertyInspector).Show(true);
			break;

		case reMainFrame_ViewProjectExplorer:
			m_wxAuiManager.GetPane(m_projectExplorer).Show(true);
			break;

		case reMainFrame_ViewOutliner:
			m_wxAuiManager.GetPane(m_outliner).Show(true);
			break;
	};
	
	m_wxAuiManager.Update();
}

void reMainFrame::OnFileExit(wxCommandEvent& event){
	CloseFrame();
}

void reMainFrame::CloseFrame(){
	Close();
}

#include "primitive/rPrimitiveBox.hpp"

void reMainFrame::OnPopulate(wxCommandEvent& event){
	rEngine* engine = m_component->GetEngine();

	rPrimitiveBox* box = new rPrimitiveBox("box01", engine);
	engine->scene->AddActor(box);
	m_viewportDisplay->Refresh();
}