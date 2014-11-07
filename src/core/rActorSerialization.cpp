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