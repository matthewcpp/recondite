#include "primitive/rPrimitive.hpp"

rPrimitive::rPrimitive(const rString& id, rEngine* engine)
	:rActor3(id, engine)
{
	m_edgeColor = rColor(200, 200, 200, 255);
	m_faceColor = rColor::White;

	m_model = nullptr;
	m_geometryInvalid = true;
	m_renderingOptions.reset(new rRenderingOptions());
}

void rPrimitive::SetColor(const rColor& color){
	m_faceColor = color;
	m_edgeColor = rColor::White;
}

void rPrimitive::SetEdgeColor(const rColor& color){
	m_edgeColor = color;
	UpdateMaterials();
}

void rPrimitive::SetFaceColor(const rColor& color){
	m_faceColor = color;
	UpdateMaterials();
}

void rPrimitive::InvalidateGeometry(){
	m_geometryInvalid = true;
}

void rPrimitive::RecreateGeometry(){
	if (!m_geometryInvalid) return;

	if (m_model)
		m_engine->content->Models()->Delete(m_model->GetName());

	recondite::ModelData modelData;

	CreateGeometry(modelData);

	rString assetName = Id() + "_model";
	m_model = m_engine->content->Models()->LoadFromData(modelData, assetName);

	UpdateMaterials();

	m_geometryInvalid = false;
}

void rPrimitive::UpdateMaterials(){
	if (m_model){

		size_t meshCount = m_model->GetTriangleMeshCount();
		for (size_t i = 0; i < meshCount; i++) {
			m_model->GetTriangleMesh(i)->GetMaterial()->SetDiffuseColor(m_faceColor);
		}

		meshCount = m_model->GetLineMeshCount();
		for (size_t i = 0; i < meshCount; i++) {
			m_model->GetLineMesh(i)->GetMaterial()->SetDiffuseColor(m_faceColor);
		}
	}
}

void rPrimitive::OnDelete(){
	if (m_model)
		m_engine->content->Models()->Delete(m_model->GetName());
}

void rPrimitive::Draw(){
	if (m_geometryInvalid){
		RecreateGeometry();
	}
		
	if (RenderingOptions()->Visible()){
		rMatrix4& transform = TransformMatrix();
		m_engine->renderer->RenderModel(m_model, transform);
	}
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
Model* rPrimitive::Model() const{
	return m_model;
}
