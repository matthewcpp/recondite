#include "reModelViewer.hpp"
#include "rProp.hpp"

reModelViewerFrame::reModelViewerFrame(reComponent* component, wxWindow* parent)
	:wxFrame(parent, wxID_ANY, "Model Viewer", wxDefaultPosition, wxSize(640, 480))
{
	_component = component;
	_currentActor = nullptr;

	CreateElements();
}

void reModelViewerFrame::CreateElements() {
	wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);
	_glCanvas = new rwxGLCanvas(_component, "Model Viewer Canvas", this);
	_glCanvas->GetCamera()->SetRenderingMask(16U);

	boxSizer->Add(_glCanvas, 1, wxALL | wxEXPAND);

	SetSizer(boxSizer);

	Bind(wxEVT_CLOSE_WINDOW, &reModelViewerFrame::OnClose, this);
}

void reModelViewerFrame::ViewModel(const wxString& name) {
	rScene* scene = _component->GetScene();
	recondite::Model* model = _component->GetEngine()->content->Models()->Get(name.c_str().AsChar());

	if (_currentActor) {
		scene->DeleteActor(_currentActor);
		scene->Flush();
	}

	if (!model) {
		wxString modelPath = _component->GetProject()->Assets()->GetAssetPath(rAssetType::Model, name);
		model = _component->GetEngine()->content->Models()->LoadFromResource(modelPath.c_str().AsChar(), name.c_str().AsChar());

		if (!model) {
			wxMessageBox("Unable to load resource for Model: " + name);
			return;
		}
	}

	recondite::Camera* camera = _glCanvas->GetCamera();
	rProp* prop = new rProp(model, "Model Viewer", _component->GetEngine());
	prop->RenderingOptions()->SetRenderingMask(16);
	scene->AddActor(prop);

	rAlignedBox3 boundingBox = prop->WorldBounding();
	rVector3 center = boundingBox.Center();
	rVector3 extent = boundingBox.Extent();

	camera->SetTarget(center);
	camera->SetPosition(center + (rVector3::BackwardVector * (extent.z * 2)));

	_currentActor = prop;

	SetTitle(name);
	Show(true);
	Iconize(false);
	Raise();

	_glCanvas->Refresh();
	
}

void reModelViewerFrame::OnClose(wxCloseEvent& event) {
	event.Veto();

	Hide();
}