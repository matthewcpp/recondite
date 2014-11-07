#include "primitive/rPrimitiveSerialization.hpp"

//---------- Box ----------

rActor3* rPrimitiveBoxReader::LoadActor(rXMLElement* element, const rString& id, rEngine* engine){
	rColor color = rColor::White;
	rVector3 vec = rVector3::ZeroVector;
	float val = 1.0f;

	rPrimitiveBox* primitiveBox = new rPrimitiveBox(id, engine);
	LoadActorProperties(element, primitiveBox);

	rXMLUtil::ReadColorFromElement(element->GetFirstChildNamed("color"), color);
	primitiveBox->SetColor(color);

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

 //---------- Cone ----------

 rActor3* rPrimitiveConeReader::LoadActor(rXMLElement* element, const rString& id, rEngine* engine){
	 rColor color = rColor::White;
	 float val = 1.0f;

	rPrimitiveCone* primitiveCone = new rPrimitiveCone(id, engine);
	LoadActorProperties(element, primitiveCone);
	
	rXMLUtil::ReadColorFromElement(element->GetFirstChildNamed("color"), color);
	primitiveCone->SetColor(color);

	rXMLElement* width = element->GetFirstChildNamed("radius");
	if (width){
		width->GetText<float>(val);
		primitiveCone->SetRadius(val);
	}

	rXMLElement* height = element->GetFirstChildNamed("height");
	if (height){
		height->GetText<float>(val);
		primitiveCone->SetHeight(val);
	}

	 return primitiveCone;
 }

 //---------- Cylinder ----------

 rActor3* rPrimitiveCylinderReader::LoadActor(rXMLElement* element, const rString& id, rEngine* engine){
	 rColor color = rColor::White;
	 float val = 1.0f;

	 rPrimitiveCylinder* primitiveCylinder = new rPrimitiveCylinder(id, engine);
	 LoadActorProperties(element, primitiveCylinder);

	rXMLUtil::ReadColorFromElement(element->GetFirstChildNamed("color"), color);
	primitiveCylinder->SetColor(color);

	rXMLElement* width = element->GetFirstChildNamed("radius");
	if (width){
		width->GetText<float>(val);
		primitiveCylinder->SetRadius(val);
	}

	rXMLElement* height = element->GetFirstChildNamed("height");
	if (height){
		height->GetText<float>(val);
		primitiveCylinder->SetHeight(val);
	}

	 return primitiveCylinder;
 }