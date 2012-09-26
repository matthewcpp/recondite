#include "rwxGlView.hpp"

rwxGLView::rwxGLView(rEngine* engine, wxWindow* parent, wxWindowID id, const int* attribList, const wxPoint& pos, const wxSize& size, long style, const wxString& name, const wxPalette& palette)
:wxGLCanvas(parent, id, attribList, pos, size, style, name, palette)
{
	m_engine = engine;
	m_viewport.graphicsDevice = m_engine->GraphicsDevice();
	
	InitSharedContextIfNecessary(this);
	
	m_camera = new rViewCamera("camera", rVector3::ZeroVector);
	m_viewport.SetCamera(m_camera);
	m_camera->SetPosition(rVector3(0.0f, 0.0f, 5.0f));
}

rwxGLView::~rwxGLView(){
	delete m_camera;
}

void rwxGLView::PrepareToDraw(){
	SetCurrent(*sharedContext);
	InitGraphicsDeviceIfNecessary();
	SetViewportSize();
	
	m_engine->GraphicsDevice()->Clear();
	m_engine->GraphicsDevice()->SetActiveViewport(m_viewport);
}

void rwxGLView::SetCamera(rCamera* camera){
	m_viewport.SetCamera(camera);
}

void rwxGLView::SetViewportSize(){
	int width,height;
	GetSize(&width,&height);
	m_viewport.SetWindowSize(width,height);	
}

bool rwxGLView::InitGraphicsDeviceIfNecessary(){
	if (m_engine->GraphicsDevice() == NULL || m_engine->GraphicsDevice()->IsInit())
		return false;
	
	m_engine->GraphicsDevice()->Init();
	return true;
}

wxGLContext* rwxGLView::sharedContext = NULL;

bool rwxGLView::InitSharedContextIfNecessary(wxGLCanvas* glCanvas){
	if (sharedContext)
		return false;
    
	sharedContext = new wxGLContext(glCanvas);
	sharedContext->SetCurrent(*glCanvas);
	return true;
}