#include "reMainFrame.hpp"

reMainFrame::reMainFrame(rwxComponent* component, reProject* project, const wxString& title, const wxPoint& pos, const wxSize& size)
	:wxFrame(NULL, wxID_ANY, title, pos, size)
{
	m_component = component;
	m_project = project;

	m_wxAuiManager.SetManagedWindow(this);

	m_toolManager = new reToolManager(m_component, this, &m_wxAuiManager);
	m_viewportDisplay = new reViewportDisplay(m_component, m_toolManager, this);
	m_propertyInspector = new rePropertyInspector(m_component, m_viewportDisplay, this);
	m_projectExplorer = new reProjectExplorer(m_component, m_project, this);
	m_outliner = new reOutliner(m_component, m_propertyInspector, this);

	
	SetMenuBar(CreateEditorMenuBar());
	CreateStatusBar();

	m_wxAuiManager.AddPane(m_viewportDisplay, wxAuiPaneInfo()
		.Center()
		.Caption("Level View")
		.CloseButton(false)
		.Hide());

	m_wxAuiManager.AddPane(m_propertyInspector, wxAuiPaneInfo()
		.Right()
		.Position(0)
		.Caption("Property Inspector")
		.Dockable(true)
		.Floatable(true)
		.MinimizeButton(true)
		.BestSize(250, 450)
		.MinSize(250, 100));

	m_wxAuiManager.AddPane(m_projectExplorer, wxAuiPaneInfo()
		.Left()
		.Position(0)
		.Caption("Project Explorer")
		.Dockable(true)
		.Floatable(true)
		.MinimizeButton(true)
		.BestSize(250, 250)
		.MinSize(250, 100));

	m_wxAuiManager.AddPane(m_outliner, wxAuiPaneInfo()
		.Left()
		.Position(1)
		.Caption("Outliner")
		.Dockable(true)
		.Floatable(true)
		.MinimizeButton(true)
		.BestSize(250, 450)
		.MinSize(250, 100));

	m_wxAuiManager.Update();
}

reMainFrame::~reMainFrame(){
	m_wxAuiManager.UnInit();
}

wxMenuBar* reMainFrame::CreateEditorMenuBar(){
	wxMenuBar* menuBar = new wxMenuBar();

	wxMenu* fileMenu = new wxMenu();

	wxMenu* newMenu = new wxMenu();
	newMenu->Append(reMainFrame_MenuNewProject, "Project...");
	newMenu->Append(reMainFrame_MenuNewLevel, "Level...");
	fileMenu->AppendSubMenu(newMenu, "New");

	fileMenu->Append(reMainFrame_MenuOpenProject, "Open Project...");

	fileMenu->AppendSeparator();
	fileMenu->Append(wxID_EXIT, "Exit\tAlt+F4");
	menuBar->Append(fileMenu, "&File");
	
	

	wxMenu* viewMenu = new wxMenu();
	viewMenu->Append(reMainFrame_ViewPropertyInspector, "Property Inspector");
	viewMenu->Append(reMainFrame_ViewProjectExplorer, "Project Explorer");
	viewMenu->Append(reMainFrame_ViewProjectExplorer, "Outliner");
	menuBar->Append(viewMenu, "&View");

	Bind(wxEVT_MENU, &reMainFrame::OnFileExit, this, wxID_EXIT);
	Bind(wxEVT_MENU, &reMainFrame::OnNewProject, this, reMainFrame_MenuNewProject);
	Bind(wxEVT_MENU, &reMainFrame::OnOpenProject, this, reMainFrame_MenuOpenProject);
	Bind(wxEVT_MENU, &reMainFrame::OnViewWindowSelection, this, reMainFrame_IdUIBegin, reMainFrame_IdUIEnd);

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

void reMainFrame::ProcessProjectOpen(){
	wxAuiPaneInfo panel = m_wxAuiManager.GetPane(m_viewportDisplay);

	if (!panel.IsShown()){
		panel.Show(true);
		m_wxAuiManager.Update();
	}
	m_projectExplorer->ShowProject();
	SetTitle("Recondite Editor - " + m_project->Name());
}

void reMainFrame::OnNewProject(wxCommandEvent& event){
	reNewProjectDialog dialog;

	if (dialog.ShowModal() == wxID_OK){
		m_project->Create(dialog.GetProjectDir(), dialog.GetProjectName());
		ProcessProjectOpen();
	}
}

void reMainFrame::OnOpenProject(wxCommandEvent& event){
	wxFileDialog projectDialog(this, "Open Project", wxEmptyString, wxEmptyString, "Recondite Projects (*.rprj)|*.rprj", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (projectDialog.ShowModal() == wxID_OK){
		bool opened = m_project->Open(projectDialog.GetPath());

		if (opened){
			ProcessProjectOpen();
		}
	}
}

void reMainFrame::OnCloseProject(wxCommandEvent& event){
	m_project->Close();

	m_projectExplorer->DeleteAllItems();
	m_outliner->DeleteAllItems();

	SetTitle("Recondite Editor");

	m_wxAuiManager.GetPane(m_viewportDisplay).Hide();
	m_wxAuiManager.Update();
}