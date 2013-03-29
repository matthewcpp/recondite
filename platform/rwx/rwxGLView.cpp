#include "rwxGLView.hpp"

rwxGLView::rwxGLView(rEngine* engine, wxWindow* parent, wxWindowID id, const int* attribList, const wxPoint& pos, const wxSize& size, long style, const wxString& name, const wxPalette& palette)
:wxGLCanvas(parent, id, attribList, pos, size, style, name, palette)
{
	m_engine = engine;
	
	//InitSharedContextIfNecessary(this);
	
	m_camera = new rViewCamera("camera", rVector3::ZeroVector);
	m_viewport.SetCamera(m_camera);
	m_camera->SetPosition(rVector3(0.0f, 0.0f, 5.0f));
}

rwxGLView::~rwxGLView(){
	delete m_camera;
}

void rwxGLView::PrepareToDraw(){
	InitSharedContextIfNecessary(this);
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
	m_viewport.SetSize(width,height);
}

bool rwxGLView::InitGraphicsDeviceIfNecessary(){
	if (!m_engine->GraphicsDevice() || m_engine->GraphicsDevice()->IsInit() || m_engine->GraphicsDevice()->HasCalledInit())
		return false;
	
	bool result = m_engine->GraphicsDevice()->Init();
	
	if (!result)
	    wxMessageBox("Error Initializing Graphics Device: " + m_engine->GraphicsDevice()->GetLastErrorMessage());
	
	return result;
}

void rwxGLView::DrawReconditeScene(){
    	PrepareToDraw();
        
        DrawScene();
        
        SwapBuffers();
}

wxGLContext* rwxGLView::sharedContext = NULL;

bool rwxGLView::InitSharedContextIfNecessary(wxGLCanvas* glCanvas){
	if (sharedContext)
		return false;
    
	sharedContext = new wxGLContext(glCanvas);
	sharedContext->SetCurrent(*glCanvas);
	return true;
}