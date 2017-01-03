#ifndef RE_TRANSLATEGIZMO_HPP
#define RE_TRANSLATEGIZMO_HPP

#include "project/reComponent.hpp"
#include "rProp.hpp"
#include "reGizmo.hpp"

class reTranslateGizmo : public reTransformGizmoBase {
public:
	reTranslateGizmo(reComponent* component);

public:
	void Update();

	reGizmoAxis PickAxis(const rRay3& ray);

private:
	void CreateGeometry();

};

#endif