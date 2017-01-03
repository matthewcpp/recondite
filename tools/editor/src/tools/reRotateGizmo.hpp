#pragma once

#include "project/reComponent.hpp"
#include "rProp.hpp"
#include "reGizmo.hpp"

class reRotateGizmo : public reTransformGizmoBase {
public:
	reRotateGizmo(reComponent* component);

public:
	void Update();

	void CreateGeometry();

	reGizmoAxis PickAxis(const rRay3& ray);
};