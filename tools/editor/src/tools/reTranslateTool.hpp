#ifndef RE_TRANSLATETOOL_HPP
#define RE_TRANSLATETOOL_HPP

#include "project/reComponent.hpp"

#include <wx/wx.h>

#include "tools/reSelectionTool.hpp"

#include "data/rModelData.hpp"
#include "primitive/rPrimitiveGeometry.hpp"
#include "rProp.hpp"

class reTranslateTool : public reSelectionTool {
public:
	reTranslateTool(reComponent* component, wxFrame* owner);

	virtual wxString GetToolName() const override;

	virtual void OnActivate() override;

private:
	void CreateGizmo();

	rModel* m_model;

public:

};

#endif