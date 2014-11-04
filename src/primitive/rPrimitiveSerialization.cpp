#include "primitive/rPrimitiveSerialization.hpp"

rActor3* rPrimitiveBoxReader::LoadActor(rXMLElement* element, const rString& id, rEngine* engine){
	rColor color = rColor::White;
	rAlignedBox3 box;

	rXMLUtil::ReadColorFromElement(element->GetFirstChildNamed("color"), color);
	rXMLUtil::ReadAlignedBox3FromFromElement(element->GetFirstChildNamed("box"), box);

	rPrimitiveBox* primitiveBox = new rPrimitiveBox(id, engine);
	primitiveBox->SetColor(color);
	primitiveBox->SetBox(box);

	return primitiveBox;
}

 bool rPrimitiveBoxWriter::SerializeActor(rActor3* actor, rXMLElement* element){
	 rPrimitiveBox* primitiveBox = static_cast<rPrimitiveBox*>(actor);

	 rXMLUtil::CreateColorElement(element, "color", primitiveBox->Color());
	 rXMLUtil::CreateAlignedBox3Element(element, "box", primitiveBox->Box());

	 return true;
 }