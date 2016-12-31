#ifndef RE_TRANSLATETOOL_HPP
#define RE_TRANSLATETOOL_HPP

#include <memory>

#include "project/reComponent.hpp"

#include <wx/wx.h>

#include "tools/reToolBase.hpp"
#include "commands/reTranslateCommand.hpp"

#include "asset/rModelData.hpp"
#include "primitive/rPrimitiveGeometry.hpp"
#include "rProp.hpp"
#include "reGizmo.hpp"

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
	void SetDragPlaneFromSelectedAxis();
	bool GetWorldSpaceDragPosition(rwxGLCanvas* canvas, rVector3& result);

private:

	reGizmo::Axis m_selectedAxis;

	rPlane m_dragPlane;
	rVector3 m_previousWorldPosition;

	reTranslateCommand* m_command;

private:
	class Gizmo : public reGizmo {
	public:
		Gizmo(reComponent* component);

	protected:
		virtual void CreateGizmoHandle(recondite::ModelData& modelData);
	};

	std::unique_ptr<Gizmo> m_gizmo;

	rNO_COPY_CLASS(reTranslateTool)
};

#endif