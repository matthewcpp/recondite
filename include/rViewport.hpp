#ifndef R_VIEWPORT_HPP
#define R_VIEWPORT_HPP

#include "rTypes.hpp"

#include "rPoint.hpp"
#include "rSize.hpp"

#include "rMatrix4.hpp"
#include "rMatrixUtil.hpp"

#include "rLine3.hpp"

#include "rCamera.hpp"

enum rViewportType{
	rVIEWPORT_PERSP,
	rVIEWPORT_ORTHO,
	rVIEWPORT_2D
};

class rViewport{
public:
	rViewport(rViewportType type = rVIEWPORT_PERSP);

	int GetSelectionRay(const rPoint& pos , rRay3& selectionRay) const;

	rCamera* Camera() const;
	void SetCamera(rCamera* camera);
	
	void SetViewportType(rViewportType type);
	rViewportType ViewportType() const;

	void SetSize(int width , int height);
	void SetSize(const rSize& size);
	
	void SetPosition(int x, int y);
	void SetPosition(const rPoint& point);

	rRect GetScreenRect() const;
	void SetScreenRect(const rRect& rect);
	void SetScreenRect(int x, int y, int width, int height);
	
	void GetProjectionMatrix(rMatrix4& matrix) const;
	void GetModelViewMatrix(rMatrix4& matrix) const;
	void GetViewProjectionMatrix(rMatrix4& matrix) const;
	
private:
	rViewportType m_type;
	rRect m_rect;
	rCamera* m_camera;
	
	float m_nearClip;
	float m_farClip;
};

#endif