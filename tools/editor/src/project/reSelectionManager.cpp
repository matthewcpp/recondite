#include "reSelectionManager.hpp"
#include "rDrawable.hpp"

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

	m_selectionColor.Set(255, 255, 0, 255);
}

void reSelectionManager::Select(const wxString& name){
	ClearSelection();
	AddSelection(name);
}

void reSelectionManager::AddSelection(const wxString& name){
	m_selectionList.push_back(name);
	ApplySelectionMaterial(name);
	reSelectionEvent event(name, m_selectionList);
	m_component->Trigger(reSELECTION_SELECT, event);
}

bool reSelectionManager::Deselect(const wxString& name){
	for (size_t i = 0; i < m_selectionList.size(); i++){
		if (m_selectionList[i] == name){
			ReapplyOriginalMaterials(m_selectionList[i]);
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
		for (size_t i = 0; i < m_selectionList.size(); i++) {
			ReapplyOriginalMaterials(m_selectionList[i]);
		}

		m_selectionList.clear();

		reSelectionEvent event;
		m_component->Trigger(reSELECTION_SELECT_NONE, event);

	}
}

const wxArrayString& reSelectionManager::GetSelection() const{
	return m_selectionList;
}

void reSelectionManager::ApplySelectionMaterial(const wxString& name) {
	rActor3* actor = m_component->GetScene()->GetActor(name.c_str().AsChar());

	if (actor->IsDrawable()) {
		rDrawable* drawable = (rDrawable*)actor;

		recondite::Model* model = drawable->GetModel();

		for (size_t i = 0; i < model->GetLineMeshCount(); i++) {
			recondite::Mesh* mesh = model->GetLineMesh(i);
			rMaterial* material = mesh->GetMaterial();

			m_cachedColorMap[material] = material->DiffuseColor();
			material->SetDiffuseColor(m_selectionColor);
		}
	}
}

void reSelectionManager::ReapplyOriginalMaterials(const wxString& name) {
	rActor3* actor = m_component->GetScene()->GetActor(name.c_str().AsChar());

	if (actor->IsDrawable()) {
		rDrawable* drawable = (rDrawable*)actor;

		recondite::Model* model = drawable->GetModel();

		for (size_t i = 0; i < model->GetLineMeshCount(); i++) {
			recondite::Mesh* mesh = model->GetLineMesh(i);
			rMaterial* material = mesh->GetMaterial();

			material->SetDiffuseColor(m_cachedColorMap[material]);
			m_cachedColorMap.erase(material);
		}
	}
}

void reSelectionManager::RenderSelection() {
	rRenderer* renderer = m_component->GetEngine()->renderer;
	rRenderMode renderMode = renderer->GetModelRenderMode();

	if (renderMode == rRenderMode::Shaded) {
		renderer->SetModelRenderMode(rRenderMode::Wireframe);

		for (size_t i = 0; i < m_selectionList.size(); i++) {
			rDrawable* drawable = (rDrawable*)m_component->GetScene()->GetActor(m_selectionList[i].c_str().AsChar());

			renderer->RenderModel(drawable->GetModel(), drawable->TransformMatrix());
		}

		renderer->SetModelRenderMode(renderMode);
	}

}