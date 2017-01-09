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
	void AddSceneActor(const wxString& category, const wxBitmap& icon, const wxString& label, const wxString createStr);
	void StartItemDrag(wxMouseEvent& event);

public:
	void OnProjectOpen();

private:
	void CreateSceneView();

private:
	reComponent* m_component;

	std::map<int, wxString> m_actorMapping;
	std::map<wxString, wxSizer*> m_categories;
	int m_nextPaletteId;
};

#endif
