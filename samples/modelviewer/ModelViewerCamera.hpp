#pragma once

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rCamera.hpp"
#include "rPoint.hpp"

#include "rActor3.hpp"

class ModelViewerCamera : public rActor3{
public:
	ModelViewerCamera(recondite::Camera* camera, const rString& name, rEngine* engine);

	virtual int Update() override;

	void SetYaw(float yaw);
	float Yaw() const;

	void SetRoll(float roll);
	float Roll() const;

	float Radius() const;
	void SetRadius(float radius);

	float Distance() const;
	void SetDistance(float distance);

	void MoveCloserIn();
	void MoveFartherAway();

	void Reset(const rVector3 target, float radius, float yaw, float roll);
	void UpdatePosition();

	float OrbitSpeed() const;
	void SetOrbitSpeed(float speed);

	void SetPanSpeed(float speed);
	float PanSpeed() const;

	virtual void SetTarget(const rVector3& target);

	virtual rString ClassName() const;

private:
	int CalculateZoomDirection(int wheelValue);

	void DoZoom(int zoomDirection);
	void DoOrbit (const rPoint& position, float timeDelta);
	void DoPan(const rPoint& position, float timeDelta);

	bool ProcessMouse();
	bool ProcessTouch();

private:
	rPoint m_lastUpdatePos;
	int m_lastWheelValue;

	float m_pinchAmount;

	bool m_dragging;
	float m_orbitSpeed;
	float m_panSpeed;

	float m_radius;
	float m_distance;

	bool m_needsUpdate;

	rVector3 m_cameraAngle;
	rVector3 m_center;
	recondite::Camera* m_camera;
};
