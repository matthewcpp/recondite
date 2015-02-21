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