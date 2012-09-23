#ifndef R_VIEWPORT_HPP
#define R_VIEWPORT_HPP

#include "rTypes.hpp"

#include "rPoint2.hpp"
#include "rSize2.hpp"

#include "rVector2.hpp"
#include "rMatrix3.hpp"
#include "rMatrix4.hpp"
#include "rLine3.hpp"

#include "rCamera.hpp"
#include "rGraphicsDevice.hpp"

enum rViewportType{
	rVIEWPORT_PERSP,
	rVIEWPORT_ORTHO,
	rVIEWPORT_2D
};

struct rViewport{
public:
	rViewport(rViewportType type = rVIEWPORT_PERSP);

	void SetWindowBottomLeft(int xx , int yy);
	void SetWindowSize(int wwidth , int hheight);

	void SetWorldTopLeft(float x , float y);

	void IncrementWorldTranslate(float tx , float ty);
	inline void SetWorldTranslate(float tx , float ty);

	inline void SetWorldScale(float k);
	
	void SetCamera(rCamera* camera);

	int GetSelectionRay(const rPoint2& pos , rRay3& selectionRay) const;

	rMatrix3 MatrixTransform2D() const;
	rMatrix4 ViewMatrix() const;

	rRectangle2 Get2DScreenRect();

	rViewportType m_type;

	rVector2 m_worldTranslate;
	float m_worldScale;

	rPoint2 m_windowPos;
	rSize2 m_windowSize;

	inline rCamera* Camera() const;
	void SetViewportType(rViewportType type);
	inline rViewportType ViewportType() const;

	rCamera* m_camera;
	rGraphicsDevice* graphicsDevice;

};

void rViewport::SetWorldScale(float k){
	m_worldScale = k;
}

void rViewport::SetWorldTranslate(float tx , float ty){
	m_worldTranslate.Set(tx , ty);
}

 rCamera* rViewport::Camera() const{
	 return m_camera;
 }

 rViewportType rViewport::ViewportType() const{
	 return m_type;
 }




#endif