#include "commands/reInsertActorCommand.hpp"

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