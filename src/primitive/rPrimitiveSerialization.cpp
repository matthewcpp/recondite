#include "primitive/rPrimitiveSerialization.hpp"

rActor3* rPrimitiveBoxReader::LoadActor(rXMLElement* element, const rString& id, rEngine* engine){
	rColor color = rColor::White;
	rVector3 vec = rVector3::ZeroVector;
	float val;

	rPrimitiveBox* primitiveBox = new rPrimitiveBox(id, engine);
	rXMLUtil::ReadColorFromElement(element->GetFirstChildNamed("color"), color);
	primitiveBox->SetColor(color);

	rXMLUtil::ReadVector3FromElement(element->GetFirstChildNamed("position"), vec);
	primitiveBox->SetPosition(vec);

	rXMLElement* width = element->GetFirstChildNamed("width");
	if (width){
		width->GetText<float>(val);
		primitiveBox->SetWidth(val);
	}

	rXMLElement* height = element->GetFirstChildNamed("height");
	if (height){
		height->GetText<float>(val);
		primitiveBox->SetHeight(val);
	}

	rXMLElement* depth = element->GetFirstChildNamed("depth");
	if (depth){
		depth->GetText<float>(val);
		primitiveBox->SetDepth(val);
	}

	return primitiveBox;
}

 bool rPrimitiveBoxWriter::SerializeActor(rActor3* actor, rXMLElement* element){
	 rPrimitiveBox* primitiveBox = static_cast<rPrimitiveBox*>(actor);

	 rXMLUtil::CreateColorElement(element, "color", primitiveBox->Color());
	 rXMLUtil::CreateAlignedBox3Element(element, "box", primitiveBox->Box());

	 return true;
 }