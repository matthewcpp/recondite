#pragma once

#include "project/reComponent.hpp"
#include "rProp.hpp"
#include "reGizmo.hpp"

class reScaleGizmo {
public:
	reScaleGizmo(reComponent* component);

public:
	void Update();
	void SetVisibility(bool visibility);

	void CreateGeometry();

	void SetPosition(const rVector3& position);

	reGizmoAxis PickAxis(const rRay3& ray);
	void HighlightAxis(reGizmoAxis axis);
	void UnhighlightAxis(reGizmoAxis axis);

private:
	reComponent* m_component;


	rProp* m_uniformScaleHandle;
};