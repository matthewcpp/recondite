#include "reMainFrame.hpp"

#include <wx/filedlg.h>
#include <wx/textdlg.h>

#include "project/reProjectBuilder.hpp"

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

	m_projectBuilder = new reProjectBuilder(m_component);
	m_modelViewer = new reModelViewerFrame(m_component, this);
	m_logWindow = new reLogWindow(m_component, this);
	m_toolManager = new reToolManager(m_component, this, &m_wxAuiManager);
	m_viewportDisplay = new reViewportDisplay(m_component, m_toolManager, this);
	m_propertyInspector = new rePropertyInspector(m_component, m_viewportDisplay, this);
	m_projectExplorer = new reProjectExplorer(this, m_modelViewer, m_component, this);
	m_outliner = new reOutliner(m_component, m_propertyInspector, this);
	m_palette = new rePalette(m_component, this);
	m_palette->Disable();

	m_splashPanel = new wxPanel(this, wxID_ANY);
	wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);
	boxSizer->Add(new wxStaticBitmap(m_splashPanel, wxID_ANY, wxBitmap("assets/r.png", wxBITMAP_TYPE_PNG)),1, wxALIGN_CENTER);
	m_splashPanel->SetSizer(boxSizer);
	
	m_component->InitGraphics(m_viewportDisplay->GetViewport("Viewport 1")->GetCanvas());

	SetMenuBar(CreateEditorMenuBar());
	CreateStatusBar();

	wxAuiToolBar* projectToolbar = new wxAuiToolBar(this);
	projectToolbar->SetToolBitmapSize(wxSize(16, 16));
	projectToolbar->AddTool(reMainFrame_NewProject, "New Project", wxBitmap("assets/action-newproject.png", wxBITMAP_TYPE_PNG));
	projectToolbar->AddTool(reMainFrame_OpenProject, "Open Project", wxBitmap("assets/action-openproject.png", wxBITMAP_TYPE_PNG));
	projectToolbar->AddTool(reMainFrame_CloseProject, "Close Project", wxBitmap("assets/action-closeproject.png", wxBITMAP_TYPE_PNG));
	projectToolbar->AddTool(reMainFrame_SaveLevel, "Save Project", wxBitmap("assets/action-save.png", wxBITMAP_TYPE_PNG));
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

	m_wxAuiManager.AddPane(m_splashPanel, wxAuiPaneInfo()
		.Center()
		.Caption("Recondite Editor")
		.CloseButton(false));

	m_wxAuiManager.AddPane(m_viewportDisplay, wxAuiPaneInfo()
		.Center()
		.Hide()
		.Caption("Level View"));

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

	m_wxAuiManager.Bind(wxEVT_AUI_PANE_CLOSE, &reMainFrame::OnAuiPaneClose, this);

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

	case reMainFrame_SaveLevel:
		SaveActiveLevel();
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

	fileMenu->Append(reMainFrame_OpenSolution, "Open Solution");
	fileMenu->Append(reMainFrame_BuildProject, "Build Project");
	fileMenu->Append(reMainFrame_BuildAndRunProject, "Build and Run Project\tCtrl+B");

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

	Bind(wxEVT_MENU, &reMainFrame::OnBuildAndRunProject, this, reMainFrame_BuildAndRunProject);
	Bind(wxEVT_MENU, &reMainFrame::OnBuildProject, this, reMainFrame_BuildProject);
	Bind(wxEVT_MENU, &reMainFrame::OnOpenSolution, this, reMainFrame_OpenSolution);

	Bind(wxEVT_CHAR_HOOK, &reMainFrame::OnCharHook, this);

	return menuBar;
}

void reMainFrame::OnAssetImportModel(wxCommandEvent& event) {
	wxFileDialog importModelDialog(this, "Open Model", wxEmptyString, wxEmptyString, wxEmptyString, wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (importModelDialog.ShowModal() == wxID_OK) {
		reProject* project = m_component->GetProject();
		recondite::Model* model = project->Assets()->ImportModel(importModelDialog.GetPath());

		if (model) {
			reModelViewerDialog dialog(m_component, model->GetName().c_str());

			if (dialog.ShowModal() == wxID_OK) {
				rString modelName = model->GetName();
				rString createString = "rProp:" + modelName;
				wxImage icon = dialog.GetThumbnail();
				m_component->GetProject()->Assets()->SetAssetIcon(icon, rAssetType::Model, model->GetName().c_str());
				m_palette->AddSceneActor("Models", wxBitmap(icon), modelName.c_str(), createString.c_str());
				m_projectExplorer->AddModel(model->GetName().c_str());

				project->SaveProjectFile();
			}
			else {
				project->Assets()->DeleteModel(model->GetName().c_str());
			}
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


	m_wxAuiManager.GetPane(m_viewportDisplay).Show(true).Position(0).Caption(str);
	m_wxAuiManager.GetPane(m_splashPanel).Hide();
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

		bool created = m_component->GetProject()->Levels()->CreateLevel(levelName);

		if (created){
			m_propertyInspector->StopInspecting();
			m_outliner->ClearOutliner();
			m_outliner->OutlineLevel();

			m_projectExplorer->AddLevel(levelName);
			EnsureViewportDisplayVisible();
			m_viewportDisplay->SetDefaultViewOrientations();
			m_viewportDisplay->UpdateAllViewports();
			m_component->GetProject()->SaveProjectFile();
		}
	}
}

void reMainFrame::SaveActiveLevel(){
	m_component->GetProject()->Levels()->SaveActiveLevel();
	m_component->MarkSaved();
}

void reMainFrame::OnCharHook(wxKeyEvent& event) {
	m_viewportDisplay->CharHook(event);

	event.Skip();
}

int UnsavedFilesPrompt() {
	return wxMessageBox(
		"Save changes before closing?",
		"Unsaved Changes",
		wxYES_NO | wxCANCEL | wxICON_QUESTION
	);
}

bool reMainFrame::ActivateLevel(const wxString& levelName) {
	if (m_component->IsDirty()) {
		int result = UnsavedFilesPrompt();
		if (result == wxCANCEL) {
			return false;
		}
		else if (result == wxYES) {
				SaveActiveLevel();
		}
	}

	m_component->ClearCommandList();
	m_component->GetProject()->Levels()->ActivateLevel(levelName);
	EnsureViewportDisplayVisible(levelName);
	m_palette->Enable();
	m_viewportDisplay->SetDefaultViewOrientations();
	m_viewportDisplay->UpdateAllViewports();

	return true;
}


void reMainFrame::OnAuiPaneClose(wxAuiManagerEvent& event) {
	if (m_component->IsDirty()) {
		int result = UnsavedFilesPrompt();
		if (result == wxCANCEL) {
			event.Veto();
		}
		else{
			if (result == wxYES) {
				SaveActiveLevel();
			}

			m_component->ClearCommandList();
			m_wxAuiManager.GetPane(m_splashPanel).Show(true).Position(0);
			m_palette->Disable();
			m_wxAuiManager.Update();
		}
	}


}

void reMainFrame::OnBuildAndRunProject(wxCommandEvent& event) {
	const wxArrayString& levels = m_component->GetProject()->Levels()->LevelNames();
	if (levels.size() == 0) return;

	wxString activeLevel = m_component->GetProject()->Levels()->GetActiveLevel();

	if (activeLevel.empty()) {
		wxSingleChoiceDialog dialog(this, "Choose Level:", "Build And Run", levels);

		if (dialog.ShowModal() == wxID_OK) {
			activeLevel = dialog.GetStringSelection();
		}
	}

	m_projectBuilder->BuildAndRun(activeLevel);
}

void reMainFrame::OnBuildProject(wxCommandEvent& event) {
	m_projectBuilder->Build();
}

void reMainFrame::OnOpenSolution(wxCommandEvent& event) {
	m_projectBuilder->Open();
}