#ifndef RWX_VIEWCAMERAINTERACTION_HPP
#define RWX_VIEWCAMERAINTERACTION_HPP

#include "rBuild.hpp"

#include <wx/wx.h>

#include "recondite.hpp"


class RECONDITE_RWX_CLASS rwxViewCameraInteraction{
public:
	rwxViewCameraInteraction(rCamera* camera);

public:

	bool OnMouseMotion(wxMouseEvent& event);
	bool OnMiddleDown(wxMouseEvent& event);
	bool OnMiddleUp(wxMouseEvent& event);
	bool OnRightDown(wxMouseEvent& event);
	bool OnRightUp(wxMouseEvent& event);
	bool OnMousewheel(wxMouseEvent& event);


	bool UpdateKeyboardInteraction();

private:
	void SetCameraTarget();

private:
	rCamera* m_camera;

	float m_cameraRotateSpeed;
	float m_cameraMoveSpeed;

	rVector3 m_cameraRotation;

	rMouseButton m_activeButton;
	wxPoint m_previousPt;
	float m_targetDistance;
};

#endif