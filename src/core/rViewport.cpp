#include "rViewport.hpp"

rViewport::rViewport(rViewportType type){
	m_type = type;

	m_windowPos.x = 0;
	m_windowPos.y = 0;
	m_windowSize.width = 0;
	m_windowSize.height = 0;

	m_worldScale = 1.0f;
	m_worldTranslate = rVector2::ZeroVector;
	m_camera = NULL;
}

void rViewport::SetWindowBottomLeft(int xx , int yy){
	m_windowPos.x = xx;
	m_windowPos.y = yy;
}

void rViewport::SetWindowSize(int wwidth , int hheight){
	m_windowSize.width = wwidth;
	m_windowSize.height = hheight;
}

void rViewport::IncrementWorldTranslate(float tx , float ty){
	m_worldTranslate.x += tx;
	m_worldTranslate.y += ty;
}

rMatrix3 rViewport::MatrixTransform2D() const{
	rMatrix3 m;
	m.SetTranslate(m_worldTranslate);
	m.SetUniformScale(m_worldScale);
	return m;
}

rMatrix4 rViewport::ViewMatrix() const{
	rMatrix4 m;
	m.SetTranslate(m_worldTranslate.x , m_worldTranslate.y, 0);
	m.SetUniformScale(m_worldScale);
	return m;
}

rRectangle2 rViewport::Get2DScreenRect(){
	rRectangle2 viewArea(m_windowPos.x , m_windowPos.y , m_windowSize.width , m_windowSize.height);
	rMatrix3 xform = MatrixTransform2D();
	xform.Invert();
	rMath::Matrix3TransformRectangle(xform, viewArea);

	return viewArea;
}

void rViewport::SetViewportType(rViewportType type){
	m_type = type;
}

//based off msdn xna example
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
