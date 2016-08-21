#ifndef R_DEMO_CAMERA_HPP
#define R_DEMO_CAMERA_HPP

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rOrbitCamera.hpp"
#include "rPoint.hpp"

class rDemoCamera : public rOrbitCamera{
public:
	rDemoCamera(const rString& name, rEngine* engine);

	virtual int Update() override;

	float OrbitSpeed() const;
	void SetOrbitSpeed(float speed);

private:
	int CalculateZoomDirection(int wheelValue);

	void DoZoom(int zoomDirection);
	void DoOrbit (const rPoint& position, float timeDelta);

	bool ProcessMouse();
	bool ProcessTouch();

private:
	rPoint m_lastUpdatePos;
	int m_lastWheelValue;

	float m_pinchAmount;

	bool m_orbiting;
	float m_orbitSpeed;
};

#endif
