#pragma once

#include <memory>

#include "project/reComponent.hpp"

#include <wx/wx.h>

#include "tools/reToolBase.hpp"
#include "tools/reScaleGizmo.hpp"
#include "commands/reTransformCommands.hpp"

class reScaleTool : public reToolBase {
public:
	reScaleTool(reComponent* component, wxFrame* owner);
	virtual ~reScaleTool();

public:
	virtual bool OnMouseDown(wxMouseEvent& event, rwxGLCanvas* canvas) override;
	virtual bool OnMouseMotion(wxMouseEvent& event, rwxGLCanvas* canvas) override;
	virtual bool OnMouseUp(wxMouseEvent& event, rwxGLCanvas* canvas) override;

	virtual wxString GetToolName() const override;
	virtual void OnActivate() override;
	virtual void OnDeactivate() override;
	virtual void OnUpdate() override;

	virtual void Init() override;

private:
	void SetDragPlaneFromSelectedAxis();
	bool GetWorldSpaceDragPosition(rwxGLCanvas* canvas, rVector3& result);

private:
	std::unique_ptr<reScaleGizmo> m_gizmo;
	reScaleCommand* m_command;

	reGizmoAxis m_selectedAxis;

	rPlane m_dragPlane;
	rVector3 m_previousWorldPosition;

	rNO_COPY_CLASS(reScaleTool)
};