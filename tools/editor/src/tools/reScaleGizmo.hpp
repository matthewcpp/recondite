#pragma once

#include "project/reComponent.hpp"
#include "rProp.hpp"
#include "reGizmo.hpp"

class reScaleGizmo : public reTransformGizmoBase {
public:
	reScaleGizmo(reComponent* component);

public:
	virtual void HighlightAxis(reGizmoAxis axis) override;
	virtual void UnhighlightAxis(reGizmoAxis axis) override;
	virtual void SetVisibility(bool visibility) override;

	virtual reGizmoHandle* GetHandle(reGizmoAxis axis) override;
	void ResetStems();

public:
	void Update();

	void CreateGeometry();

	virtual void SetPosition(const rVector3& position);

	reGizmoAxis PickAxis(const rRay3& ray);

private:
	reGizmoHandle* m_uniformScaleHandle;
	float _activeStemLength;
};

class reScaleGizmoHandle : public reGizmoHandle {
public:
	reScaleGizmoHandle(const rVector3& direction, recondite::Model* model, const rString& id, rEngine* engine);
public:

	inline void SetAnchor(const rVector3& anchor);
	virtual void Draw() override;
	virtual void UpdatePosition();
	virtual bool RayPick(const rRay3& ray, rPickResult& result) override;
	virtual void UpdateScale() override;

	inline float GetStemLength() const;
	inline void SetStemLength(float stemLength);

private:
	rVector3 _anchor;
	rVector3 _direction;
	float _stemLength;
};

inline float reScaleGizmoHandle::GetStemLength() const {
	return _stemLength;
}

inline void reScaleGizmoHandle::SetStemLength(float stemLength) {
	_stemLength = stemLength;
}