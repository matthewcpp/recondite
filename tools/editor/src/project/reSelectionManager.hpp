#ifndef RE_SELECTIONMANAGER_HPP
#define RE_SELECTIONMANAGER_HPP

#include <map>

#include "rwxComponent.hpp"

#include <wx/wx.h>

#include "rEventHandler.hpp"

class reSelectionEvent : public rEvent{
public:
	reSelectionEvent();
	reSelectionEvent(const wxString& selection, const wxArrayString& selectionList);
	reSelectionEvent(const wxArrayString& selectionList);

public:
	wxString Item() const;
	const wxArrayString& SelectionList() const;

private:
	wxString m_selection;
	wxArrayString m_selectionList;
};

enum reSelectionEventId{
	reSELECTION_DESELECT,
	reSELECTION_SELECT,
	reSELECTION_SELECT_NONE
};

class reSelectionManager{
public:
	reSelectionManager(rwxComponent* component);

public:
	void Select(const wxString& name);
	void AddSelection(const wxString& name);
	bool Deselect(const wxString& name);
	bool IsSelected(const wxString& name);
	void ClearSelection();

	const wxArrayString& GetSelection() const;

public:
	void ApplySelectionMaterial(const wxString& name);
	void ReapplyOriginalMaterials(const wxString& name);

	void RenderSelection();

private:
	wxArrayString m_selectionList;

	rwxComponent* m_component;
	std::map<rMaterial*, rColor> m_cachedColorMap;
	rColor m_selectionColor;
};

#endif