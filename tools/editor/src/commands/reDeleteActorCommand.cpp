#include "commands/reDeleteActorCommand.hpp"

reDeleteActorCommand::reDeleteActorCommand(const wxArrayString& actorList, reComponent* component)
	:wxCommand(true, "Delete Actor")
{
	m_actorList = actorList;
	m_component = component;

	SerializeActors();
}

bool reDeleteActorCommand::Do() {
	if (m_actorList.size() == 0)
		return false;

	rScene* scene = m_component->GetScene();

	for (size_t i = 0; i < m_actorList.size(); i++){
		scene->DeleteActor(m_actorList[i].c_str().AsChar());
	}

	m_component->SelectionManager()->ClearSelection();

	return true;
}

bool reDeleteActorCommand::Undo() {
	rScene* scene = m_component->GetScene();

	rXMLSerializationSource source(m_actorData.GetRoot());
	return scene->ParseActors(&source);
}

void reDeleteActorCommand::SerializeActors(){
	rScene* scene = m_component->GetScene();

	rXMLElement* root = m_actorData.CreateRoot("delete");
	rXMLSerializationTarget target(root->CreateChild("actors"));

	for (size_t i = 0; i < m_actorList.size(); i++){
		rString actorName = m_actorList[i].c_str().AsChar();

		rActor3* actor = scene->GetActor(actorName);
		actor->Save(&target);
	}
}