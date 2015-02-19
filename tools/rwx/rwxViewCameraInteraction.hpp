#ifndef RWX_VIEWCAMERAINTERACTION_HPP
#define RWX_VIEWCAMERAINTERACTION_HPP

#include "rBuild.hpp"

#include <wx/wx.h>

#include "recondite.hpp"


class RECONDITE_RWX_CLASS rwxViewCameraInteraction{
public:
	rwxViewCameraInteraction(rCamera* camera);

public:

	bool UpdateKeyboardInteraction();

private:
	rCamera* m_camera;

	float m_cameraRotateSpeed;
	float m_cameraMoveSpeed;
};

#endif