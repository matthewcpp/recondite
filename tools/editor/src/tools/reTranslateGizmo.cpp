#include "reTranslateGizmo.hpp"

reTranslateGizmo::reTranslateGizmo(reComponent* component){
	m_component = component;

	m_xHandle = nullptr;
	m_yHandle = nullptr;
	m_zHandle = nullptr;
}

reGizmoAxis reTranslateGizmo::GetGizmoAxis(rActor3* actor){
	if (actor == m_xHandle)
		return reGizmoAxis::X;
	else if (actor == m_yHandle)
		return reGizmoAxis::Y;
	else if (actor == m_zHandle)
		return reGizmoAxis::Z;
	else
		return reGizmoAxis::NONE;
}

void reTranslateGizmo::SetVisibility(bool visibility){
	m_xHandle->RenderingOptions()->SetVisibility(visibility);
	m_yHandle->RenderingOptions()->SetVisibility(visibility);
	m_zHandle->RenderingOptions()->SetVisibility(visibility);
}

void reTranslateGizmo::SetPosition(const rVector3& pos){
	m_currentPosition = pos;

	m_xHandle->SetPosition(pos);
	m_yHandle->SetPosition(pos);
	m_zHandle->SetPosition(pos);
}

rVector3 reTranslateGizmo::GetPosition(){
	return m_currentPosition;
}

void reTranslateGizmo::Update(){
	if (!m_xHandle)
		CreateGizmo();

	//the origin of the gizmo should be in the center of the selection
	const wxArrayString& selection = m_component->SelectionManager()->GetSelection();

	if (selection.size() == 0){
		SetVisibility(false);
	}
	else{
		rScene* scene = m_component->GetScene();
		rAlignedBox3 selectionBounding, actorBounding;

		for (size_t i = 0; i < selection.size(); i++){
			rActor3* actor = scene->GetActor(selection[i].c_str().AsChar());
			actorBounding = actor->BoundingVolume()->FitBox();
			selectionBounding.AddBox(actorBounding);
		}

		SetPosition(selectionBounding.Center());
		SetVisibility(true);
	}
}

void SetMeshDiffuseColors(rModel* model, const rColor& color){
	rArrayString meshNames;
	model->GetMeshNames(meshNames);

	for (size_t i = 0; i < meshNames.size(); i++){
		rMesh* mesh = model->GetMesh(meshNames[i]);
		mesh->Material()->SetDiffuseColor(color);
	}
}

void reTranslateGizmo::SetInitialHandleRenderingOptions(){
	m_xHandle->RenderingOptions()->SetForceRender(true);
	m_yHandle->RenderingOptions()->SetForceRender(true);
	m_zHandle->RenderingOptions()->SetForceRender(true);

	m_xHandle->RenderingOptions()->SetOverdraw(true);
	m_yHandle->RenderingOptions()->SetOverdraw(true);
	m_zHandle->RenderingOptions()->SetOverdraw(true);
}

using namespace recondite;

void reTranslateGizmo::CreateGizmo(){
	/*
	rEngine* engine = m_component->GetEngine();

	rMatrix4 xform, translate, rotate;
	ModelData gizmoData(rGeometryProfile::Primitive);
	rGeometryData* geometryData = gizmoData.GetGeometryData();
	rQuaternion q;

	rPrimitiveGeometry::rPrimitiveConeParams gizmoParams(0.15f, 0.6f, 15);
	float gizmoStemLength = 1.5f;

	//create Y Handle
	rPrimitiveGeometry::CreateCone(gizmoParams, *geometryData);
	translate.SetTranslate(0, gizmoStemLength, 0);
	geometryData->TransformVertices(0, translate);

	gizmoData.CreateMeshDataFromGeometry();

	rElementBufferData* wire = geometryData->GetElementBuffer(gizmoParams.wireMeshName);
	wire->ClearElementData();

	size_t startingIndex = geometryData->VertexCount();
	rVector3 handleBase(0, gizmoStemLength, 0);
	geometryData->PushVertex(rVector3::ZeroVector, rVector3::ZeroVector);
	geometryData->PushVertex(handleBase, rVector3::ZeroVector);
	wire->Push(startingIndex, startingIndex + 1);

	rModel* handleModel = engine->content->Models()->LoadFromData(gizmoData, "__reTranslateGizmoYHandle");
	SetMeshDiffuseColors(handleModel, rColor::Green);

	m_yHandle = new rProp(handleModel, "__reTranslateGizmoYHandle", m_component->GetEngine());
	m_component->AddReservedActor(m_yHandle);
	

	//create X Handle
	gizmoData.Clear();
	
	rPrimitiveGeometry::CreateCone(gizmoParams, *geometryData);
	translate.SetTranslate(gizmoStemLength, 0, 0);
	rotate.LoadIdentity();
	rotate.SetRotationZ(-90.0f);
	xform = translate * rotate;
	geometryData->TransformVertices(0, xform);

	gizmoData.CreateMeshDataFromGeometry();

	wire = geometryData->GetElementBuffer(gizmoParams.wireMeshName);
	wire->ClearElementData();

	startingIndex = geometryData->VertexCount();
	handleBase.Set(gizmoStemLength, 0, 0);
	geometryData->PushVertex(rVector3::ZeroVector, rVector3::ZeroVector);
	geometryData->PushVertex(handleBase, rVector3::ZeroVector);
	wire->Push(startingIndex, startingIndex + 1);

	handleModel = m_component->GetEngine()->content->Models()->LoadFromData(gizmoData, "__reTranslateGizmoXHandle");
	SetMeshDiffuseColors(handleModel, rColor::Blue);

	m_xHandle = new rProp(handleModel, "__reTranslateGizmoXHandle", m_component->GetEngine());
	m_component->AddReservedActor(m_xHandle);

	//create Z Handle
	gizmoData.Clear();
	rPrimitiveGeometry::CreateCone(gizmoParams, *geometryData);
	translate.SetTranslate(0, 0, gizmoStemLength);
	rotate.LoadIdentity();
	rotate.SetRotationX(90.0f);
	xform = translate * rotate;
	geometryData->TransformVertices(0, xform);

	wire = geometryData->GetElementBuffer(gizmoParams.wireMeshName);
	wire->ClearElementData();

	gizmoData.CreateMeshDataFromGeometry();

	startingIndex = geometryData->VertexCount();
	handleBase.Set(0, 0, gizmoStemLength);
	geometryData->PushVertex(rVector3::ZeroVector, rVector3::ZeroVector);
	geometryData->PushVertex(handleBase, rVector3::ZeroVector);
	wire->Push(startingIndex, startingIndex + 1);

	handleModel = m_component->GetEngine()->content->Models()->LoadFromData(gizmoData, "__reTranslateGizmoZHandle");
	m_zHandle = new rProp(handleModel, "__reTranslateGizmoZHandle", m_component->GetEngine());
	SetMeshDiffuseColors(handleModel, rColor::Red);

	m_component->AddReservedActor(m_zHandle);
	SetVisibility(false);

	SetInitialHandleRenderingOptions();
	*/
}