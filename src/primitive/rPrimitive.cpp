#include "primitive/rPrimitive.hpp"

rPrimitive::rPrimitive(const rString& id, rEngine* engine)
	:rDrawable(id, engine)
{
	m_edgeColor = rColor(200, 200, 200, 255);
	m_faceColor = rColor::White;

	m_geometryInvalid = true;
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

	recondite::ModelData modelData;
	CreateGeometry(modelData);

	recondite::MaterialData* faceMaterialData = modelData.CreateMaterial();
	faceMaterialData->diffuseColor = m_faceColor;
	modelData.GetTriangleMesh(0)->SetMaterialDataId(faceMaterialData->id);

	recondite::MaterialData* lineMaterialData = modelData.CreateMaterial();
	lineMaterialData->diffuseColor = m_edgeColor;
	modelData.GetLineMesh(0)->SetMaterialDataId(lineMaterialData->id);

	rString assetName = Id() + "_model";
	m_engine->content->Models()->Delete(assetName);
	recondite::Model* model = m_engine->content->Models()->LoadFromData(modelData, assetName);

	SetModel(model);
	m_geometryInvalid = false;
}

void rPrimitive::UpdateMaterials(){
	if (_modelInstance){
		const recondite::Model* model = _modelInstance->GetModel();

		size_t meshCount = model->GetTriangleMeshCount();
		for (size_t i = 0; i < meshCount; i++) {
			_modelInstance->GetTriangleMeshInstanceMaterial(i)->SetDiffuseColor(m_faceColor);
		}

		meshCount = model->GetLineMeshCount();
		for (size_t i = 0; i < meshCount; i++) {
			_modelInstance->GetLineMeshInstanceMaterial(i)->SetDiffuseColor(m_edgeColor);
		}
	}
}

void rPrimitive::OnDelete(){
	if (_modelInstance)
		m_engine->content->Models()->Delete(_modelInstance->GetModel()->GetName());
}

recondite::ModelInstance* rPrimitive::GetModelInstance() {
	RecreateGeometry();

	return _modelInstance.get();
}

void rPrimitive::Draw(){
	RecreateGeometry();
		
	if (RenderingOptions()->GetVisibility()){
		rMatrix4& transform = TransformMatrix();
		m_engine->renderer->RenderModel(_modelInstance.get(), transform);
	}
}

rColor rPrimitive::EdgeColor() const{
	return m_edgeColor;
}

rColor rPrimitive::FaceColor() const{
	return m_faceColor;
}

bool rPrimitive::DoSerialize(riSerializationTarget* target, rSerializeAction action){
	target->Category("Primitive");

	target->Color("faceColor", m_faceColor);
	target->Color("edgeColor", m_edgeColor);

	return rActor3::DoSerialize(target, action);
}

void rPrimitive::OnLoad(){
	rActor3::OnLoad();
	InvalidateGeometry();
	RecalculateBoundingVolume();
}

size_t rPrimitive::GetNumAssets() const {
	return 0U;
}

bool rPrimitive::GetAsset(size_t index, rAssetType& assetType, rString& name) const {
	return false;
}