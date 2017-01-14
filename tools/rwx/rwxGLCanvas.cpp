#include "rwxGLCanvas.hpp"

rwxGLCanvas::rwxGLCanvas(rwxComponent* component, const wxString& name, wxWindow *parent, wxWindowID id)
	:wxGLCanvas(parent, id, 0, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE)
{
	m_component = component;
	m_name = name;
	m_viewport = nullptr;
	m_camera = new recondite::Camera();
	m_camera->SetPosition(rVector3(0, 0, 10));

	Bind(wxEVT_PAINT, &rwxGLCanvas::OnPaint, this);
}

rwxGLCanvas::~rwxGLCanvas() {
	if (m_viewport) {
		m_component->GetEngine()->component->DeleteViewport(m_viewport->Name());
		delete m_camera;
	}
}

void rwxGLCanvas::OnPaint(wxPaintEvent& event){
	wxPaintDC dc(this);

	if (!m_component->IsReady()){
		m_component->Init(this);
	}
	
	SetCurrent(*m_component->GetContext());

	if (m_viewport == nullptr)
		CreateViewport();

	const wxSize ClientSize = GetClientSize();
	m_viewport->SetScreenRect(0, 0, ClientSize.x, ClientSize.y);
	
	m_component->RenderScene(m_viewport);

	SwapBuffers();
}

void rwxGLCanvas::CreateViewport(){
	m_viewport = m_component->CreateViewport(m_name.c_str().AsChar());
	m_viewport->SetCamera(m_camera);
}

rViewport* rwxGLCanvas::GetViewport(){
	return m_viewport;
}

recondite::Camera* rwxGLCanvas::GetCamera(){
	return m_camera;
}

wxString rwxGLCanvas::GetCanvasName() const {
	return m_name;
}