#include "commands/reTransformCommands.hpp"

//transform
reTransformCommnad::reTransformCommnad(const wxArrayString& actors, reComponent* component, const wxString& name) 
:wxCommand(true, name)
{
	_actors = actors;
	_component = component;

	_transformDelta = rVector3::ZeroVector;
	_firstCommand = true;
}

void reTransformCommnad::Update(const rVector3& delta) {
	_transformDelta += delta;
	_ApplyDelta(delta);
}

bool reTransformCommnad::Do() {
	if (_firstCommand)
		_firstCommand = false;
	else
		_ApplyDelta(_transformDelta);

	return true;
}

bool reTransformCommnad::Undo() {
	_ApplyDelta(-_transformDelta);

	return true;
}


//translate

reTranslateCommand::reTranslateCommand(const wxArrayString& actors, reComponent* component)
	:reTransformCommnad(actors, component, "Translate")
{}


void reTranslateCommand::_ApplyDelta(const rVector3& delta){
	rScene* scene = _component->GetScene();
	rVector3 position;

	for (size_t i = 0; i < _actors.size(); i++){
		rActor3* actor = scene->GetActor(_actors[i].c_str().AsChar());
		position = actor->Position();
		position += delta;
		actor->SetPosition(position);
	}
}

//rotate

reRotateCommand::reRotateCommand(const wxArrayString& actors, reComponent* component)
	:reTransformCommnad(actors, component, "Rotate")
{}

void CheckRotation(float& rotation) {
	if (rotation < -365.0f)
		rotation += 365.0f;
	else if (rotation > 365.0f)
		rotation -= 365.0f;
}

void reRotateCommand::_ApplyDelta(const rVector3& rotationDelta) {
	rScene* scene = _component->GetScene();
	rVector3 rotation;

	for (size_t i = 0; i < _actors.size(); i++) {
		rActor3* actor = scene->GetActor(_actors[i].c_str().AsChar());
		rotation = actor->Rotation();
		rotation += rotationDelta;

		CheckRotation(rotation.x);
		CheckRotation(rotation.y);
		CheckRotation(rotation.z);

		actor->SetRotation(rotation);
	}
}

//scale
reScaleCommand::reScaleCommand(const wxArrayString& actors, reComponent* component)
	:reTransformCommnad(actors, component, "Scale")
{}

void reScaleCommand::_ApplyDelta(const rVector3& scaleDelta) {
	rScene* scene = _component->GetScene();
	rVector3 scale;

	for (size_t i = 0; i < _actors.size(); i++) {
		rActor3* actor = scene->GetActor(_actors[i].c_str().AsChar());
		scale = actor->Scale();
		scale += scaleDelta;

		actor->SetScale(scale);
	}
}