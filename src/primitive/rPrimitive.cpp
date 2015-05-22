#include "primitive/rPrimitive.hpp"

rPrimitive::rPrimitive(const rString& id, rEngine* engine)
	:rActor3(id, engine)
{
	m_edgeColor = rColor(200, 200, 200, 255);
	m_faceColor = rColor::White;

	m_model = nullptr;
	m_geometryInvalid = true;

	m_drawable.reset(new rDrawable());
	m_drawable->SetShader(m_engine->content->DefaultPrimitiveShader());
}

void rPrimitive::SetColor(const rColor& color){
	m_faceColor = color;
	m_edgeColor = rColor::White;
}

void rPrimitive::SetEdgeColor(const rColor& color){
	m_edgeColor = color;

	if (m_model)
		m_model->GetMesh("wire")->Drawable()->Material()->SetDiffuseColor(m_edgeColor);
}

void rPrimitive::SetFaceColor(const rColor& color){
	m_faceColor = color;

	if (m_model)
		m_model->GetMesh("shaded")->Drawable()->Material()->SetDiffuseColor(m_faceColor);
}

void rPrimitive::InvalidateGeometry(){
	m_geometryInvalid = true;
}

void rPrimitive::RecreateGeometry(){
	if (!m_geometryInvalid) return;

	if (m_model)
		m_engine->content->RemoveModelAsset(m_model->Name());

	rModelData modelData(rGeometryProfile::PRIMITIVE);
	rGeometryData& geometryData = *modelData.GetGeometryData();

	CreateGeometry(geometryData);

	modelData.CreateMeshDataFromGeometry();

	rString assetName = Id() + "_model";
	m_model = m_engine->content->LoadModel(modelData, assetName);

	UpdateMaterials();

	m_geometryInvalid = false;
}

void rPrimitive::UpdateMaterials(){
	if (m_model){
		rArrayString meshes;
		m_model->GetMeshNames(meshes);

		for (size_t i = 0; i < meshes.size(); i++){
			rMesh* mesh = m_model->GetMesh(meshes[i]);

			rGeometryType geometryType = mesh->geometryType;

			if (geometryType == rGeometryType::LINES || geometryType == rGeometryType::LINE_LOOP)
				mesh->Drawable()->Material()->SetDiffuseColor(m_edgeColor);
			else
				mesh->Drawable()->Material()->SetDiffuseColor(m_faceColor);
		}
	}
}

void rPrimitive::OnDelete(){
	if (m_model)
		m_engine->content->RemoveModelAsset(m_model->Name());
}

void rPrimitive::Draw(){
	if (m_geometryInvalid){
		RecreateGeometry();
	}
		
	rMatrix4& transform = TransformMatrix();
	m_engine->renderer->RenderModel(m_model, transform);
}

rColor rPrimitive::EdgeColor() const{
	return m_edgeColor;
}

rColor rPrimitive::FaceColor() const{
	return m_faceColor;
}

bool rPrimitive::DoSerialize(riSerializationTarget* target){
	target->Category("Primitive");

	target->Color("faceColor", m_faceColor);
	target->Color("edgeColor", m_edgeColor);

	return rActor3::DoSerialize(target);
}

void rPrimitive::OnLoad(){
	rActor3::OnLoad();
	InvalidateGeometry();
}
rModel* rPrimitive::Model() const{
	return m_model;
}
