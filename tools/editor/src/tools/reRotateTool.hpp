#pragma once

#include <memory>

#include "project/reComponent.hpp"

#include <wx/wx.h>

#include "tools/reToolBase.hpp"
#include "tools/reRotateGizmo.hpp"
#include "commands/reTransformCommands.hpp"

class reRotateTool : public reToolBase {
public:
	reRotateTool(reComponent* component, wxFrame* owner);
	virtual ~reRotateTool();

public:
	virtual void Init() override;
	virtual void OnActivate() override;
	virtual void OnDeactivate() override;

	bool OnMouseDown(wxMouseEvent& event, rwxGLCanvas* canvas) override;
	virtual bool OnMouseMotion(wxMouseEvent& event, rwxGLCanvas* canvas) override;
	virtual bool OnMouseUp(wxMouseEvent& event, rwxGLCanvas* canvas) override;

	virtual wxString GetToolName() const override;

private:
	void SetDragPlaneFromSelectedAxis();
	bool GetWorldSpaceDragPosition(rwxGLCanvas* canvas, rVector3& result);

private:
	std::unique_ptr<reRotateGizmo> m_gizmo;
	reRotateCommand* m_command;

	reGizmoAxis m_selectedAxis;
	rPlane m_dragPlane;
	rPoint m_previousPoint;
	float m_rotationSpeed;

	rNO_COPY_CLASS(reRotateTool)
};