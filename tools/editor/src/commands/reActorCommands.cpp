#include "commands/reActorCommands.hpp"

//Insert

reInsertActorCommand::reInsertActorCommand(const wxString& actorCreateStr, const rVector3& position, reComponent* component)
	:wxCommand(true, "Insert Actor")
{
	m_actorCreateStr = actorCreateStr;
	m_position = position;
	m_component = component;

}

bool reInsertActorCommand::Do() {
	rEngine* engine = m_component->GetEngine();
	const char* actorStr = m_actorCreateStr.c_str().AsChar();

	m_actorId = engine->scene->GetDefaultActorId(actorStr);
	rActor3* actor = engine->actors->GetActorClass(actorStr, engine, m_actorId);
	engine->scene->AddActor(actor);

	actor->SetPosition(m_position);

	m_component->SelectionManager()->Select(m_actorId.c_str());

	return true;
}

bool reInsertActorCommand::Undo() {
	m_component->GetScene()->DeleteActor(m_actorId);
	return true;
}

//Delete

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

	m_component->SelectionManager()->ClearSelection();

	for (size_t i = 0; i < m_actorList.size(); i++){
		scene->DeleteActor(m_actorList[i].c_str().AsChar());
	}

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

//Rename

reRenameActorCommand::reRenameActorCommand(const wxString& oldName, const wxString& newName, reComponent* component)
	:wxCommand(true, "Rename Actor")
{
	m_oldName = oldName;
	m_newName = newName;

	m_component = component;
}

bool reRenameActorCommand::Do(){
	return m_component->GetScene()->RenameActor(m_oldName.c_str().AsChar(), m_newName.c_str().AsChar());
}
bool reRenameActorCommand::Undo(){
	return m_component->GetScene()->RenameActor(m_newName.c_str().AsChar(), m_oldName.c_str().AsChar());
}