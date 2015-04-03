#include "reComponent.hpp"

reComponent::reComponent(){
	m_project.reset(new reProject(this));
	m_selectionManager.reset(new reSelectionManager(this));
}

reSelectionManager* reComponent::GetSelection(){
	return m_selectionManager.get();
}

reProject* reComponent::GetProject(){
	return m_project.get();
}

bool reComponent::SubmitCommand(wxCommand* command){
	return m_commandProcessor.Submit(command);
}

void reComponent::InitCommandProcessor(wxMenu* editMenu){
	m_commandProcessor.SetEditMenu(editMenu);
}

void reComponent::LoadScene(const rString& name){
	rComponent::LoadScene(name);

	rPrimitiveGrid* groundPlane = new rPrimitiveGrid("__groundPlane", &m_engine);
	groundPlane->SetEdgeColor(rColor::Blue);
	groundPlane->SetWidth(100);
	groundPlane->SetDepth(100);
	groundPlane->SetRows(25);
	groundPlane->SetColumns(25);
	groundPlane->Drawable()->SetFaceVisibility(false);

	m_scene->AddActor(groundPlane);
}