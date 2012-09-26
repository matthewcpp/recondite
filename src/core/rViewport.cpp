#include "rViewport.hpp"

rViewport::rViewport(rViewportType type){
	m_type = type;

	m_windowPos.x = 0;
	m_windowPos.y = 0;
	m_windowSize.width = 0;
	m_windowSize.height = 0;

	m_camera = NULL;
}

void rViewport::SetViewportType(rViewportType type){
	m_type = type;
}

int rViewport::GetSelectionRay(const rPoint2& pos , rRay3& selectionRay) const{
	
	rVector3 nearPoint , farPoint;
	int result;

    rVector3 source((float)pos.x , (float)pos.y , 0.0f);
    result = graphicsDevice->Unproject(source, nearPoint);
	
	if (result == false)
		return false;

    source.z = 1.0;
    result =   graphicsDevice->Unproject(source, farPoint);
	
	if (result == false)
		return false;

    rVector3 direction = farPoint - nearPoint;
	direction.Normalize();

	selectionRay.Set(nearPoint, direction);
	return true;
}

void rViewport::SetCamera(rCamera* camera){
	m_camera = camera;
}

rRectangle2 rViewport::Get2DScreenRect(){
	return rRectangle2 (m_windowPos.x , m_windowPos.y , m_windowSize.width , m_windowSize.height);
}

void rViewport::SetWindowSize(int wwidth , int hheight){
	m_windowSize.width = wwidth;
	m_windowSize.height = hheight;
}