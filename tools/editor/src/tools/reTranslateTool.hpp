#ifndef RE_TRANSLATETOOL_HPP
#define RE_TRANSLATETOOL_HPP

#include <memory>

#include "project/reComponent.hpp"

#include <wx/wx.h>

#include "tools/reToolBase.hpp"
#include "tools/reTranslateGizmo.hpp"

#include "data/rModelData.hpp"
#include "primitive/rPrimitiveGeometry.hpp"
#include "rProp.hpp"

class reTranslateTool : public reToolBase {
public:
	reTranslateTool(reComponent* component, wxFrame* owner);

	virtual bool OnMouseDown(wxMouseEvent& event, rwxGLCanvas* canvas) override;

	virtual wxString GetToolName() const override;
	virtual void OnActivate() override;

public:
	std::unique_ptr<reTranslateGizmo> m_gizmo;
};

#endif