#include "reMainFrame.hpp"

reMainFrame::reMainFrame(rwxComponent* component, reProject* project, const wxString& title, const wxPoint& pos, const wxSize& size)
	:wxFrame(NULL, wxID_ANY, title, pos, size)
{
	m_component = component;
	m_project = project;

	CreateUIElements();
}

void reMainFrame::CreateUIElements(){
	m_wxAuiManager.SetManagedWindow(this);

	m_toolManager = new reToolManager(m_component, this, &m_wxAuiManager);
	m_viewportDisplay = new reViewportDisplay(m_component, m_toolManager, this);
	m_propertyInspector = new rePropertyInspector(m_component, m_viewportDisplay, this);
	m_projectExplorer = new reProjectExplorer(m_component, m_project, this);
	m_outliner = new reOutliner(m_component, m_propertyInspector, this);


	SetMenuBar(CreateEditorMenuBar());
	CreateStatusBar();

	wxAuiToolBar* projectToolbar = new wxAuiToolBar(this);
	projectToolbar->SetToolBitmapSize(wxSize(16, 16));
	projectToolbar->AddTool(reMainFrame_NewProject, "New Project", wxBitmap("assets/action-newproject.png", wxBITMAP_TYPE_PNG));
	projectToolbar->AddTool(reMainFrame_OpenProject, "Open Project", wxBitmap("assets/action-openproject.png", wxBITMAP_TYPE_PNG));
	projectToolbar->AddTool(reMainFrame_CloseProject, "Close Project", wxBitmap("assets/action-closeproject.png", wxBITMAP_TYPE_PNG));
	projectToolbar->AddTool(reMainFrame_SaveProject, "Save Project", wxBitmap("assets/action-save.png", wxBITMAP_TYPE_PNG));
	projectToolbar->AddTool(reMainFrame_NewLevel, "New Level", wxBitmap("assets/action-newlevel.png", wxBITMAP_TYPE_PNG));
	projectToolbar->Realize();

	m_wxAuiManager.AddPane(projectToolbar, wxAuiPaneInfo()
		.Name("Project Tools")
		.Caption("Project Tools")
		.ToolbarPane()
		.Top());

	m_wxAuiManager.AddPane(m_viewportDisplay, wxAuiPaneInfo()
		.Center()
		.Caption("Level View")
		.CloseButton(false)
		.Show(false));

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

	m_toolManager->CreateToolbars();

	m_wxAuiManager.Update();
}

void reMainFrame::OnProjectAction(wxCommandEvent& event){
	switch (event.GetId()){
	case reMainFrame_NewProject:
		NewProject();
		break;

	case reMainFrame_OpenProject:
		OpenProject();
		break;

	case reMainFrame_CloseProject:
		CloseProject();
		break;

	case reMainFrame_SaveProject:
		SaveProject();
		break;
	case reMainFrame_NewLevel:
		NewLevel();
		break;
	};
}

reMainFrame::~reMainFrame(){
	m_wxAuiManager.UnInit();
}

wxMenuBar* reMainFrame::CreateEditorMenuBar(){
	wxMenuBar* menuBar = new wxMenuBar();

	wxMenu* fileMenu = new wxMenu();

	wxMenu* newMenu = new wxMenu();
	newMenu->Append(reMainFrame_NewProject, "Project...");
	newMenu->Append(reMainFrame_NewLevel, "Level...");
	fileMenu->AppendSubMenu(newMenu, "New");

	fileMenu->Append(reMainFrame_OpenProject, "Open Project...");
	fileMenu->Append(reMainFrame_CloseProject, "Close");

	fileMenu->AppendSeparator();
	fileMenu->Append(wxID_EXIT, "Exit\tAlt+F4");
	menuBar->Append(fileMenu, "&File");
	
	

	wxMenu* viewMenu = new wxMenu();
	viewMenu->Append(reMainFrame_ViewPropertyInspector, "Property Inspector");
	viewMenu->Append(reMainFrame_ViewProjectExplorer, "Project Explorer");
	viewMenu->Append(reMainFrame_ViewProjectExplorer, "Outliner");
	menuBar->Append(viewMenu, "&View");

	Bind(wxEVT_MENU, &reMainFrame::OnFileExit, this, wxID_EXIT);
	Bind(wxEVT_MENU, &reMainFrame::OnProjectAction, this, reMainFrame_ProjectBegin, reMainFrame_ProjectEnd);
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

void reMainFrame::EnsureViewportDisplayVisible(const wxString& caption){
	wxString str = "Level View";
	if (!caption.IsEmpty())
		str = str + " - " + caption;


	m_wxAuiManager.GetPane(m_viewportDisplay).Show(true).Caption(str);
	m_wxAuiManager.Update();
}

void reMainFrame::ProcessProjectOpen(){
	m_projectExplorer->ShowProject();
	SetTitle("Recondite Editor - " + m_project->Name());
}

void reMainFrame::NewProject(){
	reNewProjectDialog dialog;

	if (dialog.ShowModal() == wxID_OK){
		m_project->Create(dialog.GetProjectDir(), dialog.GetProjectName());
		ProcessProjectOpen();
	}
}

void reMainFrame::OpenProject(){
	wxFileDialog projectDialog(this, "Open Project", wxEmptyString, wxEmptyString, "Recondite Projects (*.rprj)|*.rprj", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (projectDialog.ShowModal() == wxID_OK){
		bool opened = m_project->Open(projectDialog.GetPath());

		if (opened){
			ProcessProjectOpen();
		}
	}
}

void reMainFrame::CloseProject(){
	m_project->Close();

	m_projectExplorer->DeleteAllItems();
	m_outliner->DeleteAllItems();
	m_propertyInspector->StopInspecting();

	SetTitle("Recondite Editor");

	m_wxAuiManager.GetPane(m_viewportDisplay).Hide();
	m_wxAuiManager.Update();
}

void reMainFrame::NewLevel(){
	wxTextEntryDialog dialog(nullptr, "Name:", "Create a New Level");

	if (dialog.ShowModal() == wxID_OK){
		wxString levelName = dialog.GetValue();

		bool created = m_project->CreateLevel(levelName);

		if (created){
			m_propertyInspector->StopInspecting();
			m_outliner->DeleteAllItems();

			m_projectExplorer->AddLevel(levelName);
			EnsureViewportDisplayVisible();
			m_viewportDisplay->UpdateDisplay();
		}
	}
}

void reMainFrame::SaveProject(){
	m_project->SaveActiveLevel();
}