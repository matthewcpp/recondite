#ifndef RE_CAMERAPROPERTYCONNECTOR_HPP
#define RE_CAMERAPROPERTYCONNECTOR_HPP

#include "reActorPropertyConnector.hpp"

#include "rCamera.hpp"

class reCameraPropertyConnector : public reActorPropertyConnector{
public:
	reCameraPropertyConnector(rCamera* camera);

protected:
	virtual void SetClassPGProperties(wxPropertyGrid* grid);
	virtual void RefreshClassPGProperties(wxPropertyGrid* grid);

private:
	rCamera* m_camera;
};

#endif