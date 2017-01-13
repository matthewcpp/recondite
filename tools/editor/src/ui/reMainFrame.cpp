#include "reMainFrame.hpp"

#include <wx/filedlg.h>
#include <wx/textdlg.h>

reMainFrame::reMainFrame(reComponent* component, const wxString& title, const wxPoint& pos, const wxSize& size)
	:wxFrame(NULL, wxID_ANY, title, pos, size)
{
	m_component = component;
	m_fileHistory = new wxFileHistory(10);

	CreateUIElements();

	m_component->SetViewportManager(m_viewportDisplay);
}

void reMainFrame::CreateUIElements(){
	m_wxAuiManager.SetManagedWindow(this);

	m_modelViewer = new reModelViewerFrame(m_component, this);
	m_logWindow = new reLogWindow(m_component, this);
	m_toolManager = new reToolManager(m_component, this, &m_wxAuiManager);
	m_viewportDisplay = new reViewportDisplay(m_component, m_toolManager, this);
	m_propertyInspector = new rePropertyInspector(m_component, m_viewportDisplay, this);
	m_projectExplorer = new reProjectExplorer(m_modelViewer, m_component, this);
	m_outliner = new reOutliner(m_component, m_propertyInspector, this);
	m_palette = new rePalette(m_component, this);

	

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
		.Top()
		.Position(0)
		.Floatable(false)
		.Gripper(false));

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
		.BestSize(250, 450)
		.MinSize(250, 100));

	m_wxAuiManager.AddPane(m_palette, wxAuiPaneInfo()
		.Right()
		.Position(1)
		.Caption("Palette")
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

	m_wxAuiManager.AddPane(m_logWindow, wxAuiPaneInfo()
		.Caption("Log")
		.Dockable(true)
		.Floatable(true)
		.Float()
		.Hide()
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
	delete m_fileHistory;
}

wxMenuBar* reMainFrame::CreateEditorMenuBar(){
	wxMenuBar* menuBar = new wxMenuBar();

	wxMenu* fileMenu = new wxMenu();

	wxMenu* newMenu = new wxMenu();
	newMenu->Append(reMainFrame_NewProject, "Project...");
	newMenu->Append(reMainFrame_NewLevel, "Level...");
	fileMenu->AppendSubMenu(newMenu, "New");

	fileMenu->Append(reMainFrame_OpenProject, "Open Project...");
	wxMenu* recentMenu = new wxMenu();
	fileMenu->AppendSubMenu(recentMenu, "Recent Projects");

	m_fileHistory->Load(*m_component->GetConfig());
	m_fileHistory->UseMenu(recentMenu);
	m_fileHistory->AddFilesToMenu();
	

	fileMenu->Append(reMainFrame_CloseProject, "Close");

	fileMenu->AppendSeparator();
	fileMenu->Append(wxID_EXIT, "Exit\tAlt+F4");
	menuBar->Append(fileMenu, "&File");
	
	wxMenu* editMenu = new wxMenu();
	editMenu->Append(wxID_UNDO, "Undo\tCtrl+Z");
	editMenu->Append(wxID_REDO, "Redo\tCtrl+Y");
	menuBar->Append(editMenu, "&Edit");
	m_component->InitCommandProcessor(editMenu);

	wxMenu* assetMenu = new wxMenu();
	assetMenu->Append(reMainFrame_Asset_ImportModel, "Import Model...");
	menuBar->Append(assetMenu, "&Assets");

	wxMenu* viewMenu = new wxMenu();
	viewMenu->Append(reMainFrame_ViewPropertyInspector, "Property Inspector");
	viewMenu->Append(reMainFrame_ViewProjectExplorer, "Project Explorer");
	viewMenu->Append(reMainFrame_ViewOutliner, "Outliner");
	viewMenu->Append(reMainFrame_ViewPalette, "Palette");
	viewMenu->Append(reMainFrame_ViewLogWindow, "Log");
	menuBar->Append(viewMenu, "&View");

	Bind(wxEVT_MENU, &reMainFrame::OnFileExit, this, wxID_EXIT);
	Bind(wxEVT_MENU, &reMainFrame::OnUndoCommand, this, wxID_UNDO);
	Bind(wxEVT_MENU, &reMainFrame::OnRedoCommand, this, wxID_REDO);

	Bind(wxEVT_MENU, &reMainFrame::OnProjectAction, this, reMainFrame_ProjectBegin, reMainFrame_ProjectEnd);
	Bind(wxEVT_MENU, &reMainFrame::OnViewWindowSelection, this, reMainFrame_IdUIBegin, reMainFrame_IdUIEnd);
	Bind(wxEVT_MENU, &reMainFrame::OnOpenRecentProject, this, wxID_FILE1, wxID_FILE9);

	Bind(wxEVT_MENU, &reMainFrame::OnAssetImportModel, this, reMainFrame_Asset_ImportModel);

	return menuBar;
}

void reMainFrame::OnAssetImportModel(wxCommandEvent& event) {
	wxFileDialog importModelDialog(this, "Open Model", wxEmptyString, wxEmptyString, wxEmptyString, wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (importModelDialog.ShowModal() == wxID_OK) {
		reProject* project = m_component->GetProject();
		recondite::Model* model = project->Assets()->ImportModel(importModelDialog.GetPath());

		if (model) {
			rString modelName = model->GetName();
			rString createString = "rProp:" + modelName;

			m_palette->AddSceneActor("Models", wxBitmap("assets/tool-box.png", wxBITMAP_TYPE_PNG), modelName.c_str(), createString.c_str());
			m_projectExplorer->AddModel(model->GetName().c_str());

			project->SaveProjectFile();
		}
	}
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

		case reMainFrame_ViewPalette:
			m_wxAuiManager.GetPane(m_palette).Show(true);
			break;

		case reMainFrame_ViewLogWindow:
			m_wxAuiManager.GetPane(m_logWindow).Show(true);
			break;
	};
	
	m_wxAuiManager.Update();
}

void reMainFrame::OnOpenRecentProject(wxCommandEvent& event) {
	wxString recentProject = m_fileHistory->GetHistoryFile(event.GetId() - wxID_FILE1);
	bool opened = m_component->GetProject()->Open(recentProject);
	ProcessProjectOpen(recentProject);
}

void reMainFrame::OnFileExit(wxCommandEvent& event){
	CloseFrame();
}

void reMainFrame::OnUndoCommand(wxCommandEvent& event){
	m_component->UndoCommand();
}

void reMainFrame::OnRedoCommand(wxCommandEvent& event){
	m_component->RedoCommand();
}

void reMainFrame::CloseFrame(){
	m_fileHistory->Save(*m_component->GetConfig());
	Close();
}

void reMainFrame::EnsureViewportDisplayVisible(const wxString& caption){
	wxString str = "Level View";
	if (!caption.IsEmpty())
		str = str + " - " + caption;


	m_wxAuiManager.GetPane(m_viewportDisplay).Show(true).Caption(str);
	m_wxAuiManager.Update();
}

void reMainFrame::ProcessProjectOpen(const wxString& path){
	m_projectExplorer->ShowProject();
	m_palette->OnProjectOpen();

	SetTitle("Recondite Editor - " + m_component->GetProject()->Name());

	m_fileHistory->AddFileToHistory(path);
}

void reMainFrame::NewProject(){
	reNewProjectDialog dialog;

	if (dialog.ShowModal() == wxID_OK){
		reProject* project = m_component->GetProject();

		project->Create(dialog.GetProjectDir(), dialog.GetProjectName());
		ProcessProjectOpen(project->ProjectFilePath());
	}
}

void reMainFrame::OpenProject(){
	wxFileDialog projectDialog(this, "Open Project", wxEmptyString, wxEmptyString, "Recondite Projects (*.rprj)|*.rprj", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (projectDialog.ShowModal() == wxID_OK){
		wxString projectPath = projectDialog.GetPath();
		bool opened = m_component->GetProject()->Open(projectPath);

		if (opened){
			ProcessProjectOpen(projectPath);
		}
	}
}

void reMainFrame::CloseProject(){
	m_component->GetProject()->Close();

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

		bool created = m_component->GetProject()->CreateLevel(levelName);

		if (created){
			m_propertyInspector->StopInspecting();
			m_outliner->ClearOutliner();
			m_outliner->OutlineLevel();

			m_projectExplorer->AddLevel(levelName);
			EnsureViewportDisplayVisible();
			m_viewportDisplay->UpdateAllViewports();
		}
	}
}

void reMainFrame::SaveProject(){
	m_component->GetProject()->SaveActiveLevel();
}