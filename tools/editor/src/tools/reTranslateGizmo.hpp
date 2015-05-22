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

	reGizmoAxis GetGizmoAxis(rActor3* actor);
	rVector3 GetPosition();

private:
	void CreateGizmo();
	void SetInitialHandleRenderingOptions();

	void SetPosition(const rVector3& pos);
	
private:
	reComponent* m_component;

	rVector3 m_currentPosition;

	rProp* m_xHandle;
	rProp* m_yHandle;
	rProp* m_zHandle;
};

#endif