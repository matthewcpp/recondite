#include "rViewport.hpp"

rViewport::rViewport(const rString& name, rViewportType type){
	m_type = type;
	m_camera = NULL;
	
	m_rect.Set(0,0,0,0);
	m_name = name;
	SetClipping(0.2f, 5000.0f);
	m_fovY = 45.0f;

	m_renderMode = rRenderMode::Shaded;
}

void rViewport::SetNearClip(float nearClip){
	m_nearClip = nearClip;
}

float rViewport::NearClip() const{
	return m_nearClip;
}

void rViewport::SetFarClip(float farClip){
	m_farClip = farClip;
}

float rViewport::FarClip() const{
	return m_farClip;
}

void rViewport::SetClipping(float near, float far){
	m_farClip = far;
	m_nearClip = near;
}

int rViewport::GetSelectionRay(const rPoint& pos , rRay3& selectionRay) const{
    rMatrix4 projection, view;
    GetProjectionMatrix(projection);
    GetViewMatrix(view);
    
    rVector3 nearPoint , farPoint;
    int result;
    

	rVector3 source((float)pos.x , m_rect.height - (float)pos.y , 0.0f);
    result = rMatrixUtil::Unproject(source, view, projection, m_rect, nearPoint);
	
	if (result == false)
		return false;

    source.z = 1.0f;
    result = rMatrixUtil::Unproject(source, view, projection, m_rect, farPoint);
	
	if (result == false)
		return false;

    rVector3 direction = farPoint - nearPoint;
	direction.Normalize();

	selectionRay.Set(nearPoint, direction);
	return true;
}

void rViewport::GetProjectionMatrix(rMatrix4& matrix) const{
	switch (m_type){
	case rVIEWPORT_PERSP:
		rMatrixUtil::Perspective(m_fovY, (float)m_rect.width / m_rect.height, m_nearClip, m_farClip, matrix);
		break;
		
	case rVIEWPORT_ORTHO: {
		float viewportWidth = m_camera->GetWidth() / 2;
		float viewportHeight = m_camera->GetHeight() / 2;

		rMatrixUtil::Ortho(-viewportWidth, viewportWidth, -viewportHeight, viewportHeight, m_nearClip, m_farClip, matrix);
		break;
	}
		
	case rVIEWPORT_2D:
		rMatrixUtil::Ortho2D(m_rect.Left(), m_rect.Right(), m_rect.Bottom(), m_rect.Top(), matrix);
		break;
	};
}

void rViewport::GetViewMatrix(rMatrix4& matrix) const{
	if (m_camera)
		rMatrixUtil::LookAt(m_camera->GetPosition(), m_camera->GetTarget(), m_camera->GetUp(), matrix);
}

void rViewport::GetViewProjectionMatrix(rMatrix4& matrix) const{
	rMatrix4 projection, view;

	GetProjectionMatrix(projection);
	GetViewMatrix(view);

	matrix = projection * view;
}

recondite::Camera* rViewport::Camera() const{
	return m_camera;
}

void rViewport::SetCamera(recondite::Camera* camera){
	m_camera = camera;
}

void rViewport::SetViewportType(rViewportType type){
	m_type = type;
}

rViewportType rViewport::ViewportType() const{
	return m_type;
}


void rViewport::SetSize(int width , int height){
	m_rect.SetSize(width, height);
}

void rViewport::SetSize(const rSize& size){
	m_rect.SetSize(size);
}

rSize rViewport::Size() const{
	return m_rect.Size();
}

void rViewport::SetPosition(int x, int y){
	m_rect.SetPosition(x,y);
}

void rViewport::SetPosition(const rPoint& point){
	m_rect.SetPosition(point);
}

rRect rViewport::GetScreenRect() const{
	return m_rect;
}

void rViewport::SetScreenRect(const rRect& rect){
	m_rect = rect;
}

void rViewport::SetScreenRect(int x, int y, int width, int height){
	m_rect.Set(x, y, width, height);
}

void rViewport::GetViewFrustrum(rFrustrum& frustrum) const{
	rMatrix4 view;
	GetViewProjectionMatrix(view);

	rMatrixUtil::ExtractViewFrustrum(view, frustrum);
}

rString rViewport::Name() const{
	return m_name;
}

void rViewport::SetFovY(float fovy){
	m_fovY = fovy;
}

float rViewport::FovY() const{
	return m_fovY;
}

rRenderMode rViewport::RenderMode() const{
	return m_renderMode;
}

void rViewport::SetRenderMode(rRenderMode renderMode){
	m_renderMode = renderMode;
}