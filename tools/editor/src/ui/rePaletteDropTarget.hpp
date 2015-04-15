#ifndef RE_PALETTEDROPTARGET_HPP
#define RE_PALETTEDROPTARGET_HPP

#include "project/reComponent.hpp"
#include "commands/reInsertActorCommand.hpp"

#include "rwxGLCanvas.hpp"

#include <wx/wx.h>
#include <wx/dnd.h>

class rePaletteDropTarget : public wxTextDropTarget{
public:
	rePaletteDropTarget(reComponent* component, rwxGLCanvas* canvas);

	virtual bool OnDropText(wxCoord x, wxCoord y, const wxString &data);

private:
	reComponent* m_component;
	rwxGLCanvas* m_canvas;
};

#endif