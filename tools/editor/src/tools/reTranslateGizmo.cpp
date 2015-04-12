#include "reTranslateGizmo.hpp"

reTranslateGizmo::reTranslateGizmo(reComponent* component){
	m_component = component;
	m_prop = nullptr;
}

bool reTranslateGizmo::ContainsActor(rActor3* actor){
	return m_prop == actor;
}

void reTranslateGizmo::SetVisibility(bool visibility){
	m_prop->Drawable()->SetVisibility(visibility);
}

void reTranslateGizmo::SetPosition(const rVector3& position){
	m_prop->SetPosition(position);
}

void reTranslateGizmo::Update(){
	if (!m_prop)
		CreateGizmo();
}

void reTranslateGizmo::CreateGizmo(){
	rMatrix4 xform, translate, rotate;
	rModelData gizmoData(rGeometryProfile::VERTEXCOLOR);
	rVertexColorGeometryData* geometryData = (rVertexColorGeometryData*)gizmoData.GetGeometryData();
	rQuaternion q;

	float gizmoRadius = 0.15f;
	float gizmoHeight = 0.6f;
	float gizmoStemLength = 1.5f;
	size_t gizmoSegmentCount = 15;

	//create the handles
	rPrimitiveGeometry::CreateCone(gizmoRadius, gizmoHeight, gizmoSegmentCount, *geometryData);
	geometryData->SetColorForVertices(0, rColor::Green);
	translate.SetTranslate(0, gizmoStemLength, 0);
	geometryData->TransformVertices(0, translate);

	size_t startingIndex = geometryData->VertexCount();
	rPrimitiveGeometry::CreateCone(gizmoRadius, gizmoHeight, gizmoSegmentCount, *geometryData);
	geometryData->SetColorForVertices(startingIndex, rColor::Blue);
	translate.SetTranslate(gizmoStemLength, 0, 0);
	rotate.LoadIdentity();
	rotate.SetRotationZ(-90.0f);
	xform = translate * rotate;
	geometryData->TransformVertices(startingIndex, xform);

	startingIndex = geometryData->VertexCount();
	rPrimitiveGeometry::CreateCone(gizmoRadius, gizmoHeight, gizmoSegmentCount, *geometryData);
	geometryData->SetColorForVertices(startingIndex, rColor::Red);
	translate.SetTranslate(0, 0, gizmoStemLength);
	rotate.LoadIdentity();
	rotate.SetRotationX(90.0f);
	xform = translate * rotate;
	geometryData->TransformVertices(startingIndex, xform);

	//create the stems
	rElementBufferData* wire = geometryData->GetElementBuffer("wire");
	wire->ClearElementData();

	startingIndex = geometryData->VertexCount();
	rVector3 handleBase(0, gizmoStemLength, 0);
	geometryData->PushVertex(rVector3::ZeroVector, rVector3::ZeroVector, rColor::Green);
	geometryData->PushVertex(handleBase, rVector3::ZeroVector, rColor::Green);
	wire->Push(startingIndex, startingIndex + 1);

	startingIndex = geometryData->VertexCount();
	handleBase.Set(gizmoStemLength, 0, 0);
	geometryData->PushVertex(rVector3::ZeroVector, rVector3::ZeroVector, rColor::Blue);
	geometryData->PushVertex(handleBase, rVector3::ZeroVector, rColor::Blue);
	wire->Push(startingIndex, startingIndex + 1);

	startingIndex = geometryData->VertexCount();
	handleBase.Set(0, 0, gizmoStemLength);
	geometryData->PushVertex(rVector3::ZeroVector, rVector3::ZeroVector, rColor::Red);
	geometryData->PushVertex(handleBase, rVector3::ZeroVector, rColor::Red);
	wire->Push(startingIndex, startingIndex + 1);


	gizmoData.CreateMeshDataFromGeometry();

	rModel* gizmoModel = m_component->GetEngine()->content->LoadModel(gizmoData, "__reTranslateGizmo");
	m_prop = new rProp(gizmoModel, "__reTranslateGizmo", m_component->GetEngine());
	m_component->AddReservedActor(m_prop);

	SetVisibility(false);
}