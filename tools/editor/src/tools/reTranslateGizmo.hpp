#ifndef RE_TRANSLATEGIZMO_HPP
#define RE_TRANSLATEGIZMO_HPP

#include "project/reComponent.hpp"
#include "rProp.hpp"

enum class reGizmoAxis{ NONE, X, Y, Z };

class reTranslateGizmo{
public:
	reTranslateGizmo(reComponent* component);

public:
	void SetVisibility(bool visibility);
	void Update();

	reGizmoAxis PickAxis(const rRay3& ray);
	rVector3 GetPosition();

	void HighlightAxis(reGizmoAxis axis);
	void UnhighlightAxis(reGizmoAxis axis);

private:
	void CreateGeometry();

	void SetPosition(const rVector3& pos);
	
private:
	reComponent* m_component;

	rVector3 m_currentPosition;

	rProp* m_xHandle;
	rProp* m_yHandle;
	rProp* m_zHandle;
};

#endif