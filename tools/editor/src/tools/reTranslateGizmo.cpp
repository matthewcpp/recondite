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
	m_xHandle->Drawable()->SetVisibility(visibility);
	m_yHandle->Drawable()->SetVisibility(visibility);
	m_zHandle->Drawable()->SetVisibility(visibility);
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

void reTranslateGizmo::CreateGizmo(){
	rMatrix4 xform, translate, rotate;
	rModelData gizmoData(rGeometryProfile::VERTEXCOLOR);
	rVertexColorGeometryData* geometryData = (rVertexColorGeometryData*)gizmoData.GetGeometryData();
	rQuaternion q;

	float gizmoRadius = 0.15f;
	float gizmoHeight = 0.6f;
	float gizmoStemLength = 1.5f;
	size_t gizmoSegmentCount = 15;

	//create Y Handle
	rPrimitiveGeometry::CreateCone(gizmoRadius, gizmoHeight, gizmoSegmentCount, *geometryData);
	geometryData->SetColorForVertices(0, rColor::Green);
	translate.SetTranslate(0, gizmoStemLength, 0);
	geometryData->TransformVertices(0, translate);

	rElementBufferData* wire = geometryData->GetElementBuffer("wire");
	wire->ClearElementData();

	gizmoData.CreateMeshDataFromGeometry();

	size_t startingIndex = geometryData->VertexCount();
	rVector3 handleBase(0, gizmoStemLength, 0);
	geometryData->PushVertex(rVector3::ZeroVector, rVector3::ZeroVector, rColor::Green);
	geometryData->PushVertex(handleBase, rVector3::ZeroVector, rColor::Green);
	wire->Push(startingIndex, startingIndex + 1);

	rModel* handleModel = m_component->GetEngine()->content->LoadModel(gizmoData, "__reTranslateGizmoYHandle");
	handleModel->GetMesh("wire")->Drawable()->Material()->SetDiffuseColor(rColor::Green);
	m_yHandle = new rProp(handleModel, "__reTranslateGizmoYHandle", m_component->GetEngine());
	m_yHandle->Drawable()->SetShader(m_component->GetEngine()->content->DefaultPrimitiveShader());
	m_component->AddReservedActor(m_yHandle);

	//create X Handle
	gizmoData.Clear();
	rPrimitiveGeometry::CreateCone(gizmoRadius, gizmoHeight, gizmoSegmentCount, *geometryData);
	geometryData->SetColorForVertices(0, rColor::Blue);
	translate.SetTranslate(gizmoStemLength, 0, 0);
	rotate.LoadIdentity();
	rotate.SetRotationZ(-90.0f);
	xform = translate * rotate;
	geometryData->TransformVertices(0, xform);

	wire = geometryData->GetElementBuffer("wire");
	wire->ClearElementData();

	gizmoData.CreateMeshDataFromGeometry();

	startingIndex = geometryData->VertexCount();
	handleBase.Set(gizmoStemLength, 0, 0);
	geometryData->PushVertex(rVector3::ZeroVector, rVector3::ZeroVector, rColor::Blue);
	geometryData->PushVertex(handleBase, rVector3::ZeroVector, rColor::Blue);
	wire->Push(startingIndex, startingIndex + 1);

	

	handleModel = m_component->GetEngine()->content->LoadModel(gizmoData, "__reTranslateGizmoXHandle");
	handleModel->GetMesh("wire")->Drawable()->Material()->SetDiffuseColor(rColor::Blue);
	m_xHandle = new rProp(handleModel, "__reTranslateGizmoXHandle", m_component->GetEngine());
	m_xHandle->Drawable()->SetShader(m_component->GetEngine()->content->DefaultPrimitiveShader());
	m_component->AddReservedActor(m_xHandle);

	//create Z Handle
	gizmoData.Clear();
	rPrimitiveGeometry::CreateCone(gizmoRadius, gizmoHeight, gizmoSegmentCount, *geometryData);
	geometryData->SetColorForVertices(0, rColor::Red);
	translate.SetTranslate(0, 0, gizmoStemLength);
	rotate.LoadIdentity();
	rotate.SetRotationX(90.0f);
	xform = translate * rotate;
	geometryData->TransformVertices(0, xform);

	wire = geometryData->GetElementBuffer("wire");
	wire->ClearElementData();

	gizmoData.CreateMeshDataFromGeometry();

	startingIndex = geometryData->VertexCount();
	handleBase.Set(0, 0, gizmoStemLength);
	geometryData->PushVertex(rVector3::ZeroVector, rVector3::ZeroVector, rColor::Red);
	geometryData->PushVertex(handleBase, rVector3::ZeroVector, rColor::Red);
	wire->Push(startingIndex, startingIndex + 1);



	handleModel = m_component->GetEngine()->content->LoadModel(gizmoData, "__reTranslateGizmoZHandle");
	handleModel->GetMesh("wire")->Drawable()->Material()->SetDiffuseColor(rColor::Red);
	m_zHandle = new rProp(handleModel, "__reTranslateGizmoZHandle", m_component->GetEngine());
	m_zHandle->Drawable()->SetShader(m_component->GetEngine()->content->DefaultPrimitiveShader());

	m_component->AddReservedActor(m_zHandle);
	SetVisibility(false);
}