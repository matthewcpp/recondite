#include "commands/reTransformCommands.hpp"

//translate

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

//rotate

reRotateCommand::reRotateCommand(const wxArrayString& actors, reComponent* component)
	:wxCommand("Rotate") 
{
	m_actors = actors;
	m_component = component;

	m_firstCommand = true;

	m_rotationDelta = rVector3::ZeroVector;
}

bool reRotateCommand::Do() {
	if (m_firstCommand)
		m_firstCommand = false;
	else
		AddActorRotation(m_rotationDelta);

	return true;
}

bool reRotateCommand::Undo() {
	if (m_firstCommand)
		m_firstCommand = false;
	else
		AddActorRotation(-m_rotationDelta);

	return true;
}

void reRotateCommand::Update(const rVector3& rotationDelta) {
	m_rotationDelta += rotationDelta;
	AddActorRotation(rotationDelta);
}

void CheckRotation(float& rotation) {
	if (rotation < -365.0f)
		rotation += 365.0f;
	else if (rotation > 365.0f)
		rotation -= 365.0f;
}

void reRotateCommand::AddActorRotation(const rVector3& rotationDelta) {
	rScene* scene = m_component->GetScene();
	rVector3 rotation;

	for (size_t i = 0; i < m_actors.size(); i++) {
		rActor3* actor = scene->GetActor(m_actors[i].c_str().AsChar());
		rotation = actor->Rotation();
		rotation += rotationDelta;

		CheckRotation(rotation.x);
		CheckRotation(rotation.y);
		CheckRotation(rotation.z);

		actor->SetRotation(rotation);
	}
}