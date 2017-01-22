#include "reComponent.hpp"

reComponent::reComponent(){
	m_project.reset(new reProject(this));
	m_resourceManager.reset(new reProjectResourceManager(m_project.get()));
	SetResourceManager(m_resourceManager.get());
	m_selectionManager.reset(new reSelectionManager(this));
	m_viewportManager = nullptr;

	m_config.reset(new wxFileConfig("recondite_editor"));
}

reSelectionManager* reComponent::SelectionManager(){
	return m_selectionManager.get();
}

reProject* reComponent::GetProject(){
	return m_project.get();
}

bool reComponent::IsDirty() {
	return m_commandProcessor.IsDirty();
}

void reComponent::MarkSaved() {
	m_commandProcessor.MarkAsSaved();
}

void reComponent::ClearCommandList() {
	m_commandProcessor.ClearCommands();
}

bool reComponent::UndoCommand(){
	bool result = m_commandProcessor.Undo();

	if (result){
		rEvent event;
		Trigger(reCommandProcessed, event);
	}

	return result;
}

bool reComponent::RedoCommand(){
	bool result = m_commandProcessor.Redo();

	if (result){
		rEvent event;
		Trigger(reCommandProcessed, event);
	}

	return result;
}

bool reComponent::SubmitCommand(wxCommand* command){
	bool result = m_commandProcessor.Submit(command);

	if (result){
		rEvent event;
		Trigger(reCommandProcessed, event);
	}

	return result;
}

void reComponent::InitCommandProcessor(wxMenu* editMenu){
	m_commandProcessor.SetEditMenu(editMenu);
}

bool reComponent::Init(){
	bool result = rwxComponent::Init();

	m_project->Assets()->Init();

	return result;
}

void reComponent::AfterSceneRendered(rViewport* viewport){
	m_selectionManager->RenderSelection();
}

void reComponent::SetViewportManager(reViewportManager* viewportManager) {
	m_viewportManager = viewportManager;
}

reViewportManager* reComponent::GetViewportManager() {
	return m_viewportManager;
}

wxConfigBase* reComponent::GetConfig() {
	return m_config.get();
}