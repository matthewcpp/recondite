#include "reModelViewer.hpp"
#include "rProp.hpp"

reModelViewerPanel::reModelViewerPanel(reComponent* component, const wxString& name, wxWindow* parent)
	:wxPanel(parent, wxID_ANY)
{
	_component = component;
	_currentActor = nullptr;

	CreateElements(name);
}

void reModelViewerPanel::CreateElements(const wxString& name){
	wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);
	_glCanvas = new rwxGLCanvas(_component, name, this);
	_glCanvas->GetCamera()->SetRenderingMask(16U);

	boxSizer->Add(_glCanvas, 1, wxALL | wxEXPAND);

	SetSizer(boxSizer);
}

void reModelViewerPanel::ClearModel() {
	rScene* scene = _component->GetScene();

	if (_currentActor) {
		scene->DeleteActor(_currentActor);
		scene->Flush();

		_currentActor = nullptr;
	}
}

bool reModelViewerPanel::ViewModel(const wxString& name) {
	rScene* scene = _component->GetScene();
	recondite::Model* model = _component->GetEngine()->content->Models()->Get(name.c_str().AsChar());

	ClearModel();

	if (!model) {
		wxString modelPath = _component->GetProject()->Assets()->GetAssetPath(rAssetType::Model, name);
		model = _component->GetEngine()->content->Models()->LoadFromResource(modelPath.c_str().AsChar(), name.c_str().AsChar());

		if (!model) {
			return false;
		}
	}

	recondite::Camera* camera = _glCanvas->GetCamera();
	wxString propName = _glCanvas->GetCanvasName() + ':' + name;
	rProp* prop = new rProp(model, propName.c_str().AsChar(), _component->GetEngine());
	prop->RenderingOptions()->SetRenderingMask(16);
	scene->AddActor(prop);

	rAlignedBox3 boundingBox = prop->WorldBounding();
	rVector3 center = boundingBox.Center();
	rVector3 extent = boundingBox.Extent();

	camera->SetTarget(center);
	camera->SetPosition(center + (rVector3::BackwardVector * (extent.z * 2)));

	_currentActor = prop;

	_glCanvas->Refresh();

	return true;
}

reModelViewerFrame::reModelViewerFrame(reComponent* component, wxWindow* parent)
	:wxFrame(parent, wxID_ANY, "Model Viewer", wxDefaultPosition, wxSize(640, 480))
{
	CreateElements(component);
}

void reModelViewerFrame::CreateElements(reComponent* component) {
	wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);
	_modelViewer = new reModelViewerPanel(component, "Model Viewer Frame", this);

	boxSizer->Add(_modelViewer, 1, wxALL | wxEXPAND);

	SetSizer(boxSizer);

	Bind(wxEVT_CLOSE_WINDOW, &reModelViewerFrame::OnClose, this);
}


bool reModelViewerFrame::ViewModel(const wxString& name) {
	if (_modelViewer->ViewModel(name)) {
		SetTitle(name);
		Show(true);
		Iconize(false);
		Raise();

		return true;
	}
	else {
		wxMessageBox("Unable to load resource for Model: " + name);
		return false;
	}
}

void reModelViewerFrame::OnClose(wxCloseEvent& event) {
	_modelViewer->ClearModel();

	event.Veto();
	Hide();
}


reModelViewerDialog::reModelViewerDialog(reComponent* component, const wxString& name)
	:wxDialog(nullptr, wxID_ANY, name, wxDefaultPosition, wxSize(640, 480))
{
	CreateElements(component);
	_modelViewer->ViewModel(name);
}

void reModelViewerDialog::CreateElements(reComponent* component) {
	wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);
	_modelViewer = new reModelViewerPanel(component, "Model Viewer Dialog", this);

	boxSizer->Add(_modelViewer, 1, wxALL | wxEXPAND);
	boxSizer->Add(CreateStdDialogButtonSizer(wxOK | wxCANCEL | wxOK_DEFAULT), 0, wxEXPAND);

	SetSizer(boxSizer);

	Bind(wxEVT_CLOSE_WINDOW, &reModelViewerDialog::OnClose, this);
	Bind(wxEVT_BUTTON, &reModelViewerDialog::OnButton, this, wxID_OK);
	Bind(wxEVT_BUTTON, &reModelViewerDialog::OnButton, this, wxID_CANCEL);
}

void reModelViewerDialog::OnClose(wxCloseEvent& event) {
	_modelViewer->ClearModel();
	event.Skip();
}

void reModelViewerDialog::OnButton(wxCommandEvent& event) {
	_modelViewer->ClearModel();
	event.Skip();
}