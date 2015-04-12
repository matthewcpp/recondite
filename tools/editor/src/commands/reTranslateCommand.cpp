#include "commands/reTranslateCommand.hpp"

reTranslateCommand::reTranslateCommand(const wxArrayString& actors, reComponent* component)
	:wxCommand(true, "Translate")
{
	m_actors = actors;
	m_component = component;

	m_firstCommand = true;

	translateVector = rVector3::ZeroVector;
}

void reTranslateCommand::Update(const rVector3& delta){
	translateVector += delta;
	AddActorPositions(delta);
}

bool reTranslateCommand::Do() {
	if (m_firstCommand)
		m_firstCommand = false;
	else
		AddActorPositions(translateVector);
	
	return true;
}

bool reTranslateCommand::Undo() {
	AddActorPositions(-translateVector);

	return true;
}

void reTranslateCommand::AddActorPositions(const rVector3& delta){
	rScene* scene = m_component->GetScene();
	rVector3 position;

	for (size_t i = 0; i < m_actors.size(); i++){
		rActor3* actor = scene->GetActor(m_actors[i].c_str().AsChar());
		position = actor->Position();
		position += delta;
		actor->SetPosition(position);
	}
}