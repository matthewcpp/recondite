#include "reSelectionManager.hpp"

reSelectionEvent::reSelectionEvent(){}

reSelectionEvent::reSelectionEvent(const wxString& selection, const wxArrayString& selectionList){
	m_selection = selection;
}

reSelectionEvent::reSelectionEvent(const wxArrayString& selectionList){
	m_selectionList = selectionList;
}

wxString reSelectionEvent::Item() const{
	return m_selection;
}
const wxArrayString& reSelectionEvent::SelectionList() const{
	return m_selectionList;
}

//---------------------------------------------------

reSelectionManager::reSelectionManager(rwxComponent* component){
	m_component = component;
}

void reSelectionManager::Select(const wxString& name){
	ClearSelection();
	AddSelection(name);
}

void reSelectionManager::AddSelection(const wxString& name){
	m_selectionList.push_back(name);

	reSelectionEvent event(name, m_selectionList);
	m_component->Trigger(reSELECTION_SELECT, event);
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
	if (m_selectionList.size() > 0){
		m_selectionList.clear();

		reSelectionEvent event;
		m_component->Trigger(reSELECTION_SELECT_NONE, event);

	}
	else{
		m_selectionList.clear();
	}
	
}

const wxArrayString& reSelectionManager::GetSelection() const{
	return m_selectionList;
}

void reSelectionManager::RenderSelectionBounding(rEngine* engine){

	for (size_t i = 0; i < m_selectionList.size(); i++){
		rActor3* actor = m_component->GetScene()->GetActor(m_selectionList[i].c_str().AsChar());
		riBoundingVolume* boundingVolume = actor->BoundingVolume();

		if (boundingVolume){
			rAlignedBox3 b = boundingVolume->FitBox();
			//engine->renderer->RenderWireBox(b, rColor::Red);
		}
	}

}