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

	m_component->GetScene()->Bind(rEVT_SCENE_CLEAR, this, &reSelectionManager::OnSceneClear);
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
}

const wxArrayString& reSelectionManager::GetSelection() const{
	return m_selectionList;
}

void reSelectionManager::RenderSelection() {
	rRenderer* renderer = m_component->GetEngine()->renderer;

	rRenderMode renderMode = renderer->GetModelRenderMode();
	rGraphicsDevice::DepthFunction depthFunction = renderer->GetDepthFunction();

	renderer->SetModelRenderMode(rRenderMode::Wireframe);
	renderer->SetDepthFunction(rGraphicsDevice::DepthFunction::LessEqual);

	std::vector<rColor> colorCache;
	std::vector<bool> instanceSet;

	for (size_t i = 0; i < m_selectionList.size(); i++) {
		rDrawable* drawable = (rDrawable*)m_component->GetScene()->GetActor(m_selectionList[i].c_str().AsChar());
		recondite::ModelInstance* modelInstance = drawable->GetModelInstance();

		const recondite::Model* model = drawable->GetModelInstance()->GetModel();

		for (size_t i = 0; i < model->GetLineMeshCount(); i++) {
			instanceSet.push_back(modelInstance->HasTriangleInstanceMaterialSet(i));
			colorCache.push_back(modelInstance->GetLineMeshMaterial(i)->DiffuseColor());

			modelInstance->GetLineMeshInstanceMaterial(i)->SetDiffuseColor(m_selectionColor);
		}

		renderer->RenderModel(modelInstance, drawable->TransformMatrix());

		for (size_t i = 0; i < model->GetLineMeshCount(); i++) {
			if (instanceSet[i]) {
				modelInstance->GetLineMeshInstanceMaterial(i)->SetDiffuseColor(colorCache[i]);
			}
			else {
				modelInstance->DeleteLineMeshInstanceMaterial(i);
			}
		}
	}

	renderer->SetModelRenderMode(renderMode);
	renderer->SetDepthFunction(depthFunction);
}

void reSelectionManager::OnSceneClear(rEvent& event) {
	ClearSelection();
}