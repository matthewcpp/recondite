#ifndef R_VIEWPORT_HPP
#define R_VIEWPORT_HPP

#include "rTypes.hpp"

#include "rPoint2.hpp"
#include "rSize2.hpp"

#include "rMatrix4.hpp"
#include "rLine3.hpp"

#include "rCamera.hpp"
#include "rGraphicsDevice.hpp"

enum rViewportType{
	rVIEWPORT_PERSP,
	rVIEWPORT_ORTHO,
	rVIEWPORT_2D
};

class rViewport{
public:
	rViewport(rViewportType type = rVIEWPORT_PERSP);
	
	void SetCamera(rCamera* camera);

	int GetSelectionRay(const rPoint2& pos , rRay3& selectionRay) const;

	rRectangle2 Get2DScreenRect();

	rViewportType m_type;

	rPoint2 m_windowPos;
	rSize2 m_windowSize;

	inline rCamera* Camera() const;
	void SetViewportType(rViewportType type);
	inline rViewportType ViewportType() const;

	void SetWindowSize(int wwidth , int hheight);

	rCamera* m_camera;
	rGraphicsDevice* graphicsDevice;

};

 rCamera* rViewport::Camera() const{
	 return m_camera;
 }

 rViewportType rViewport::ViewportType() const{
	 return m_type;
 }

#endif