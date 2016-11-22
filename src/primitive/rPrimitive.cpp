#include "primitive/rPrimitive.hpp"

rPrimitive::rPrimitive(const rString& id, rEngine* engine)
	:rDrawable(id, engine)
{
	m_edgeColor = rColor(200, 200, 200, 255);
	m_faceColor = rColor::White;

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

	if (_model)
		m_engine->content->Models()->Delete(_model->GetName());

	recondite::ModelData modelData;

	CreateGeometry(modelData);

	MaterialData* faceMaterial = modelData.CreateMaterial();
	faceMaterial->diffuseColor = m_faceColor;

	MaterialData* lineMaterial = modelData.CreateMaterial();
	lineMaterial->diffuseColor = m_edgeColor;

	for (size_t i = 0; i < modelData.GetTriangleMeshCount(); i++) {
		modelData.GetTriangleMesh(i)->SetMaterialId(0);
	}

	for (size_t i = 0; i < modelData.GetLineMeshCount(); i++) {
		modelData.GetLineMesh(i)->SetMaterialId(1);
	}

	rString assetName = Id() + "_model";
	_model = m_engine->content->Models()->LoadFromData(modelData, assetName);

	m_geometryInvalid = false;
}

void rPrimitive::UpdateMaterials(){
	if (_model){

		size_t meshCount = _model->GetTriangleMeshCount();
		for (size_t i = 0; i < meshCount; i++) {
			_model->GetTriangleMesh(i)->GetMaterial()->SetDiffuseColor(m_faceColor);
		}

		meshCount = _model->GetLineMeshCount();
		for (size_t i = 0; i < meshCount; i++) {
			_model->GetLineMesh(i)->GetMaterial()->SetDiffuseColor(m_edgeColor);
		}
	}
}

void rPrimitive::OnDelete(){
	if (_model)
		m_engine->content->Models()->Delete(_model->GetName());
}

void rPrimitive::Draw(){
	if (m_geometryInvalid){
		RecreateGeometry();
	}
		
	if (RenderingOptions()->GetVisibility()){
		rMatrix4& transform = TransformMatrix();
		m_engine->renderer->RenderModel(_model, transform);
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

