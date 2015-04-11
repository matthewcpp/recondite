#include "tools/reTranslateTool.hpp"

reTranslateTool::reTranslateTool(reComponent* component, wxFrame* owner)
	: reSelectionTool(component, owner)
{
	m_model = nullptr;
}

void reTranslateTool::OnActivate(){
	if (!m_model)
		CreateGizmo();
}

void reTranslateTool::CreateGizmo(){
	rMatrix4 xform, translate, rotate;
	rModelData gizmoData(rGeometryProfile::VERTEXCOLOR);
	rVertexColorGeometryData* geometryData = (rVertexColorGeometryData*)gizmoData.GetGeometryData();
	
	rPrimitiveGeometry::CreateCone(0.25f, 0.5f, 15, *geometryData);
	geometryData->SetColorForVertices(0, rColor::Green);
	translate.SetTranslate(0, 1, 0);
	geometryData->TransformVertices(0, translate);
	
	size_t startingIndex = geometryData->VertexCount();
	rPrimitiveGeometry::CreateCone(0.25f, 0.5f, 15, *geometryData);
	geometryData->SetColorForVertices(startingIndex, rColor::Blue);
	translate.SetTranslate(1, 0, 0);
	rotate.LoadIdentity();
	rotate.SetRotationZ(-90.0f);
	xform = translate * rotate;
	geometryData->TransformVertices(startingIndex, xform);

	startingIndex = geometryData->VertexCount();
	rPrimitiveGeometry::CreateCone(0.25f, 0.5f, 15, *geometryData);
	geometryData->SetColorForVertices(startingIndex, rColor::Red);
	translate.SetTranslate(0, 0, 1);
	rotate.LoadIdentity();
	rotate.SetRotationX(-90.0f);
	xform = translate * rotate;
	geometryData->TransformVertices(startingIndex, xform);

	geometryData->RemoveElementBuffer("wire");
	
	gizmoData.CreateMeshDataFromGeometry();

	rModel* gizmoModel = m_component->GetEngine()->content->LoadModel(gizmoData, "__reTranslateGizmo");
	rProp* gizmo = new rProp(gizmoModel, "__reTranslateGizmo", m_component->GetEngine());
	m_component->AddReservedActor(gizmo);
}

wxString reTranslateTool::GetToolName() const{
	return "Translate Tool";
}