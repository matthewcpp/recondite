#include "rActorSerialization.hpp"

void riActorLoader::LoadActorProperties(rXMLElement* element, rActor3* actor){
	rVector3 vec = rVector3::ZeroVector;

	if (rXMLUtil::ReadVector3FromElement(element->GetFirstChildNamed("position"), vec))
		actor->SetPosition(vec);

	if (rXMLUtil::ReadVector3FromElement(element->GetFirstChildNamed("rotation"), vec))
		actor->SetRotation(vec);

	if (rXMLUtil::ReadVector3FromElement(element->GetFirstChildNamed("scale"), vec))
		actor->SetScale(vec);
}

bool riActorSerializer::SerializeActor(rActor3* actor, riSerializationTarget* target){
	target->SetStringProperty("id", actor->Id());
	target->SetVector3Property("position", actor->Position());
	target->SetVector3Property("rotation", actor->Rotation());
	target->SetVector3Property("scale", actor->Scale());

	return true;
}