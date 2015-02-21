#include "reSelectionManager.hpp"

reSelectionManager::reSelectionManager(rwxComponent* component){
	m_component = component;
}

void reSelectionManager::Select(const wxString& name){
	ClearSelection();
	AddSelection(name);
}

void reSelectionManager::AddSelection(const wxString& name){
	m_selectionList.push_back(name);
}

bool reSelectionManager::Deselect(const wxString& name){
	for (size_t i = 0; i < m_selectionList.size(); i++){
		if (m_selectionList[i] == name){
			m_selectionList.RemoveAt(i);
			return true;
		}
	}

	return false;
}

bool reSelectionManager::IsSelected(const wxString& name){
	for (auto& selection : m_selectionList){
		if (selection == name)
			return true;
	}

	return false;
}

void reSelectionManager::ClearSelection(){
	m_selectionList.clear();
}

const wxArrayString& reSelectionManager::GetSelection() const{
	return m_selectionList;
}