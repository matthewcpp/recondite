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

void rwxGLCanvas::Render() {
	wxPaintDC dc(this);

	if (!m_component->IsReady()) {
		m_component->Init(this);
	}

	SetCurrent(*m_component->GetContext());

	if (m_viewport == nullptr)
		CreateViewport();

	const wxSize clientSize = GetClientSize();
	m_viewport->SetScreenRect(0, 0, clientSize.x, clientSize.y);

	m_component->RenderScene(m_viewport);
}

void rwxGLCanvas::OnPaint(wxPaintEvent& event){
	Render();
	SwapBuffers();
}

void rwxGLCanvas::CreateViewport(){
	m_viewport = m_component->CreateViewport(m_name.c_str().AsChar());
	m_viewport->SetCamera(m_camera);
}

rViewport* rwxGLCanvas::GetViewport(){
	if (m_viewport == nullptr)
		CreateViewport();

	return m_viewport;
}

recondite::Camera* rwxGLCanvas::GetCamera(){
	return m_camera;
}

wxString rwxGLCanvas::GetCanvasName() const {
	return m_name;
}

rwxGLImageCanvas::rwxGLImageCanvas(rwxComponent* component, const wxString& name, wxWindow *parent, wxWindowID id)
	:rwxGLCanvas(component, name, parent, id) 
{

}

void rwxGLImageCanvas::Render() {
	rwxGLCanvas::Render();

	const wxSize clientSize = GetClientSize();
	uint8_t* buffer = new uint8_t[clientSize.x * clientSize.y * 3];

	m_component->GetEngine()->renderer->ReadActiveFramebuffer(m_viewport->GetScreenRect(), buffer);
	_image.SetData(buffer, clientSize.x, clientSize.y);
}

wxImage rwxGLImageCanvas::GetImage() {
	return _image.Mirror(false);
}