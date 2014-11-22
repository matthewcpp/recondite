#ifndef R_VIEWPORT_HPP
#define R_VIEWPORT_HPP

#include "rBuild.hpp"

#include "rString.hpp"

#include "rPoint.hpp"
#include "rSize.hpp"

#include "rMatrix4.hpp"
#include "rMatrixUtil.hpp"

#include "rLine3.hpp"

#include "interface/riCamera.hpp"

#include "rFrustrum.hpp"

enum rViewportType{
	rVIEWPORT_PERSP,
	rVIEWPORT_ORTHO,
	rVIEWPORT_2D
};

class RECONDITE_API rViewport{
public:
	rViewport(const rString& name, rViewportType type = rVIEWPORT_PERSP);

	int GetSelectionRay(const rPoint& pos , rRay3& selectionRay) const;

	riCamera* Camera() const;
	void SetCamera(riCamera* camera);
	
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
	void GetViewMatrix(rMatrix4& matrix) const;
	void GetViewProjectionMatrix(rMatrix4& matrix) const;
	
	void SetNearClip(float nearClip);
	float NearClip() const;

	void SetFarClip(float farClip);
	float FarClip() const;

	void SetClipping(float near, float far);
	void GetViewFrustrum(rFrustrum& frustrum) const;

	rString Name() const;

private:
	rViewportType m_type;
	rRect m_rect;
	riCamera* m_camera;

	rString m_name;
	
	float m_nearClip;
	float m_farClip;
};

#endif
