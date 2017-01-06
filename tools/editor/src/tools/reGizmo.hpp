#pragma once

#include "rProp.hpp"
#include "project/reComponent.hpp"

enum class reGizmoAxis { NONE, X, Y, Z, ALL };

class reGizmoHandle : public rProp {
public:
	reGizmoHandle(recondite::Model* model, const rString& id, rEngine* engine);

public:
	virtual void Draw() override;
	virtual bool RayPick(const rRay3& ray, rPickResult& result) override;

	inline void SetRenderModeOverride(rRenderMode renderModeOverride);
	inline rRenderMode GetRenderModeOverride() const;
	inline float GetScaleFactor() const;

	virtual void UpdateScale();

	virtual size_t GetNumAssets() const;
	virtual bool GetAsset(size_t index, rAssetType& assetType, rString& name);

protected:
	rRenderMode _renderModeOverride;
	float _scaleFactor;
};

inline void reGizmoHandle::SetRenderModeOverride(rRenderMode renderModeOverride) {
	_renderModeOverride = renderModeOverride;
}

inline rRenderMode reGizmoHandle::GetRenderModeOverride() const {
	return _renderModeOverride;
}

inline float reGizmoHandle::GetScaleFactor() const {
	return _scaleFactor;
}

class reTransformGizmoBase {
public:
	reTransformGizmoBase(reComponent* m_component);

public:
	virtual void HighlightAxis(reGizmoAxis axis);
	virtual void UnhighlightAxis(reGizmoAxis axis);
	virtual void SetVisibility(bool visibility);
	virtual void SetPosition(const rVector3& position);
	rVector3 GetPosition() const;

	virtual reGizmoHandle* GetHandle(reGizmoAxis axis);

protected:
	static void SetModelInstanceColor(rProp* handle, const rColor& color);

protected:
	reComponent* m_component;

	rVector3 m_currentPosition;

	reGizmoHandle* m_xHandle;
	reGizmoHandle* m_yHandle;
	reGizmoHandle* m_zHandle;
};