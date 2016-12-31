#pragma once

#include "project/reComponent.hpp"
#include "rProp.hpp"

#include "asset/rModelData.hpp"

class reGizmo {
public:
	enum class Axis { NONE, X, Y, Z };

public:
	reGizmo(reComponent* component);

public:
	void SetVisibility(bool visibility);
	void Update();

	Axis PickAxis(const rRay3& ray);
	rVector3 GetPosition();

	void HighlightAxis(Axis axis);
	void UnhighlightAxis(Axis axis);

private:
	void SetPosition(const rVector3& pos);
	void CreateGeometry();

protected:
	virtual void CreateGizmoHandle(recondite::ModelData& modelData) = 0;

protected:
	reComponent* m_component;

private:

	rVector3 m_currentPosition;

	rProp* m_xHandle;
	rProp* m_yHandle;
	rProp* m_zHandle;
};