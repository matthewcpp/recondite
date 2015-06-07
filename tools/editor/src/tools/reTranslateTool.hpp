#ifndef RE_TRANSLATETOOL_HPP
#define RE_TRANSLATETOOL_HPP

#include <memory>

#include "project/reComponent.hpp"

#include <wx/wx.h>

#include "tools/reToolBase.hpp"
#include "tools/reTranslateGizmo.hpp"
#include "commands/reTranslateCommand.hpp"

#include "asset/rModelData.hpp"
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
	virtual void OnUpdate() override;

private:
	void SetDragPlaneFromSelectedAxis();
	bool GetWorldSpaceDragPosition(rwxGLCanvas* canvas, rVector3& result);

public:
	std::unique_ptr<reTranslateGizmo> m_gizmo;

	reGizmoAxis m_selectedAxis;

	rPlane m_dragPlane;
	rVector3 m_previousWorldPosition;

	reTranslateCommand* m_command;
};

#endif