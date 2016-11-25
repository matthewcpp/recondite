#include "reComponent.hpp"

reComponent::reComponent(){
	m_project.reset(new reProject(this));
	m_selectionManager.reset(new reSelectionManager(this));
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

void reComponent::AddReservedActor(rActor3* actor){
	m_reservedActors.insert(actor->Id());
	m_scene->AddActor(actor);
}

bool reComponent::IsReservedActor(const rString& id){
	return m_reservedActors.count(id) > 0;
}

bool reComponent::SaveScene(const rString& path){
	return SaveSceneXML(path, [&](rActor3* actor)->bool {
		return m_reservedActors.count(actor->Id()) == 0;
	});
}

void reComponent::ClearScene(){
	m_scene->DeleteActors([&](rActor3* actor)->bool {
		return m_reservedActors.count(actor->Id()) == 0;
	});
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