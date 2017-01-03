#include "reComponent.hpp"

reComponent::reComponent(){
	m_project.reset(new reProject(this));
	m_selectionManager.reset(new reSelectionManager(this));
	m_viewportManager = nullptr;
}

reSelectionManager* reComponent::SelectionManager(){
	return m_selectionManager.get();
}

reProject* reComponent::GetProject(){
	return m_project.get();
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

void reComponent::OnSceneLoad(rEvent& event){

}

bool reComponent::Init(wxGLCanvas* canvas){
	bool result = rwxComponent::Init(canvas);

	if (result){
		m_scene->Bind(rEVT_SCENE_LOAD_END, this, &reComponent::OnSceneLoad);
	}

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