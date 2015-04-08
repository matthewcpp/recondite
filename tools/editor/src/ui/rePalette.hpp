#ifndef RE_PALETTE_HPP
#define RE_PALETTE_HPP

#include <map>

#include "project/reComponent.hpp"

#include <wx/wx.h>
#include <wx/dnd.h>

class rePalette : public wxPanel{
public:
	rePalette(reComponent* component, wxWindow* parent);

public:
	void AddSceneActor(wxBitmap& icon, const wxString& label, const wxString createStr);
	void StartItemDrag(wxMouseEvent& event);
private:
	void CreateSceneView();

private:
	std::map<int, wxString> m_actorMapping;
	int m_nextPaletteId;
};

#endif