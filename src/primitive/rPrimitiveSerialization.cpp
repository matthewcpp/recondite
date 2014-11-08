#include "primitive/rPrimitiveSerialization.hpp"

//---------- Primitive ----------

void rPrimitiveReader::LoadPrimitiveProperties(rXMLElement* element, rPrimitive* primitive){
	rColor color = rColor::White;

	rXMLUtil::ReadColorFromElement(element->GetFirstChildNamed("color"), color);
	primitive->SetColor(color);
}

//---------- Box ----------

rActor3* rPrimitiveBoxReader::LoadActor(rXMLElement* element, const rString& id, rEngine* engine){
	rVector3 vec = rVector3::ZeroVector;
	float fVal = 1.0f;

	rPrimitiveBox* primitiveBox = new rPrimitiveBox(id, engine);
	LoadActorProperties(element, primitiveBox);
	LoadPrimitiveProperties(element, primitiveBox);

	rXMLElement* node = element->GetFirstChildNamed("width");
	if (node){
		node->GetText<float>(fVal);
		primitiveBox->SetWidth(fVal);
	}

	node = element->GetFirstChildNamed("height");
	if (node){
		node->GetText<float>(fVal);
		primitiveBox->SetHeight(fVal);
	}

	node = element->GetFirstChildNamed("depth");
	if (node){
		node->GetText<float>(fVal);
		primitiveBox->SetDepth(fVal);
	}

	return primitiveBox;
}

 //---------- Cone ----------

 rActor3* rPrimitiveConeReader::LoadActor(rXMLElement* element, const rString& id, rEngine* engine){
	 float fVal = 1.0f;
	 int iVal = 0;

	rPrimitiveCone* primitiveCone = new rPrimitiveCone(id, engine);
	LoadActorProperties(element, primitiveCone);
	LoadPrimitiveProperties(element, primitiveCone);
	

	rXMLElement* node = element->GetFirstChildNamed("radius");
	if (node){
		node->GetText<float>(fVal);
		primitiveCone->SetRadius(fVal);
	}

	node = element->GetFirstChildNamed("height");
	if (node){
		node->GetText<float>(fVal);
		primitiveCone->SetHeight(fVal);
	}

	node = element->GetFirstChildNamed("segmentCount");
	if (node){
		node->GetText<int>(iVal);
		primitiveCone->SetSegmentCount(iVal);
	}

	 return primitiveCone;
 }

 //---------- Cylinder ----------

 rActor3* rPrimitiveCylinderReader::LoadActor(rXMLElement* element, const rString& id, rEngine* engine){
	 float fVal = 1.0f;
	 int iVal = 0;

	 rPrimitiveCylinder* primitiveCylinder = new rPrimitiveCylinder(id, engine);
	 LoadActorProperties(element, primitiveCylinder);
	 LoadPrimitiveProperties(element, primitiveCylinder);


	rXMLElement* node = element->GetFirstChildNamed("radius");
	if (node){
		node->GetText<float>(fVal);
		primitiveCylinder->SetRadius(fVal);
	}

	node = element->GetFirstChildNamed("height");
	if (node){
		node->GetText<float>(fVal);
		primitiveCylinder->SetHeight(fVal);
	}

	node = element->GetFirstChildNamed("segmentCount");
	if (node){
		node->GetText<int>(iVal);
		primitiveCylinder->SetSegmentCount(iVal);
	}

	 return primitiveCylinder;
 }

 //---------- Sphere ----------
 rActor3* rPrimitiveSphereReader::LoadActor(rXMLElement* element, const rString& id, rEngine* engine){
	float fVal = 1.0f;
	int iVal = 0;

	rPrimitiveSphere* primitiveSphere = new rPrimitiveSphere(id, engine);
	LoadActorProperties(element, primitiveSphere);
	LoadPrimitiveProperties(element, primitiveSphere);

	rXMLElement* node = element->GetFirstChildNamed("radius");
	if (node){
		node->GetText<float>(fVal);
		primitiveSphere->SetRadius(fVal);
	}

	node = element->GetFirstChildNamed("rings");
	if (node){
		node->GetText<int>(iVal);
		primitiveSphere->SetRings(iVal);
	}

	node = element->GetFirstChildNamed("sectors");
	if (node){
		node->GetText<int>(iVal);
		primitiveSphere->SetSectors(iVal);
	}

	 return primitiveSphere;
 }

 //---------- Grid ----------

 rActor3* rPrimitiveGridReader::LoadActor(rXMLElement* element, const rString& id, rEngine* engine){
	float fVal = 1.0f;
	int iVal = 0;

	rPrimitiveGrid* primitiveGrid = new rPrimitiveGrid(id, engine);
	LoadActorProperties(element, primitiveGrid);
	LoadPrimitiveProperties(element, primitiveGrid);

	rXMLElement* node = element->GetFirstChildNamed("width");
	if (node){
		node->GetText<float>(fVal);
		primitiveGrid->SetWidth(fVal);
	}

	node = element->GetFirstChildNamed("depth");
	if (node){
		node->GetText<float>(fVal);
		primitiveGrid->SetDepth(fVal);
	}

	node = element->GetFirstChildNamed("rows");
	if (node){
		node->GetText<int>(iVal);
		primitiveGrid->SetRows(iVal);
	}

	node = element->GetFirstChildNamed("columns");
	if (node){
		node->GetText<int>(iVal);
		primitiveGrid->SetColumns(iVal);
	}

	return primitiveGrid;
 }