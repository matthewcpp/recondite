#include "rwxGLCanvas.hpp"

rwxGLCanvas::rwxGLCanvas(rwxComponent* component, wxWindow *parent, wxWindowID id)
	:wxGLCanvas(parent, id, 0, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE)
{
	m_component = component;
	Bind(wxEVT_PAINT, &rwxGLCanvas::OnPaint, this);
}

void rwxGLCanvas::OnPaint(wxPaintEvent& event){
	wxPaintDC dc(this);

	if (!m_component->IsReady()){
		m_component->Init(this);
	}
	
	SetCurrent(*m_component->GetContext());

	const wxSize ClientSize = GetClientSize();
	glViewport(0, 0, ClientSize.x, ClientSize.y);
	m_component->GraphicsDevice()->Clear();

	SwapBuffers();
}