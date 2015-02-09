#include "rwxGLCanvas.hpp"

rwxGLCanvas::rwxGLCanvas(rwxComponent* component, const wxString& name, wxWindow *parent, wxWindowID id)
	:wxGLCanvas(parent, id, 0, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE)
{
	m_component = component;
	m_name = name;
	m_viewport = nullptr;
	Bind(wxEVT_PAINT, &rwxGLCanvas::OnPaint, this);
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

	wxString cameraName = m_name + "_camera";
	rViewCamera* camera = new rViewCamera(m_name.c_str().AsChar(), m_component->GetEngine());
	m_viewport->SetCamera(camera);
	camera->SetPosition(0, 0, 10);
}

rViewport* rwxGLCanvas::GetViewport(){
	return m_viewport;
}