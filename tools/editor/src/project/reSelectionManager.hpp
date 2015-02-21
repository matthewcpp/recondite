#ifndef RE_SELECTIONMANAGER_HPP
#define RE_SELECTIONMANAGER_HPP

#include "rwxComponent.hpp"

#include <wx/wx.h>

#include "rEventHandler.hpp"

class reSelectionManager{
public:
	reSelectionManager(rwxComponent* component);

	void Select(const wxString& name);
	void AddSelection(const wxString& name);
	bool Deselect(const wxString& name);
	bool IsSelected(const wxString& name);
	void ClearSelection();

	const wxArrayString& GetSelection() const;

private:
	wxArrayString m_selectionList;

	rwxComponent* m_component;
};

#endif