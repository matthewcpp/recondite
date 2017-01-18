#ifndef RE_TRANSLATETOOL_HPP
#define RE_TRANSLATETOOL_HPP

#include <memory>

#include "project/reComponent.hpp"

#include <wx/wx.h>

#include "tools/reToolBase.hpp"
#include "tools/reTranslateGizmo.hpp"
#include "commands/reTransformCommands.hpp"

#include "primitive/rPrimitiveGeometry.hpp"
#include "rProp.hpp"

class reTranslateTool : public reToolBase {
public:
	reTranslateTool(reComponent* component, wxFrame* owner);
	virtual ~reTranslateTool();

	virtual bool OnMouseDown(wxMouseEvent& event, rwxGLCanvas* canvas) override;
	virtual bool OnMouseMotion(wxMouseEvent& event, rwxGLCanvas* canvas) override;
	virtual bool OnMouseUp(wxMouseEvent& event, rwxGLCanvas* canvas) override;

	virtual wxString GetToolName() const override;
	virtual void OnActivate() override;
	virtual void OnDeactivate() override;
	virtual void OnUpdate() override;

	virtual void Init() override;

private:
	bool GetWorldSpaceDragPosition(rwxGLCanvas* canvas, rVector3& result);

public:
	std::unique_ptr<reTranslateGizmo> m_gizmo;

	reGizmoAxis m_selectedAxis;

	rPlane m_dragPlane;
	rVector3 m_previousWorldPosition;

	reTranslateCommand* m_command;

	rNO_COPY_CLASS(reTranslateTool)
};

#endif