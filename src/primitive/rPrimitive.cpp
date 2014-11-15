#include "primitive/rPrimitive.hpp"

rPrimitive::rPrimitive(const rString& id, rEngine* engine)
	:rActor3(id, engine)
{
	m_color = rColor::White;
	m_geometry = NULL;
	m_geometryInvalid = true;
}

void rPrimitive::SetColor(const rColor& color){
	m_color = color;
}

rColor rPrimitive::Color() const{
	return m_color;
}

void rPrimitive::InvalidateGeometry(){
	m_geometryInvalid = true;
}

void rPrimitive::RecreateGeometry(){
	if (m_geometry)
		m_engine->content->RemoveGeometryAsset(m_geometry->Name());

	rGeometryData geometryData;
	CreateGeometry(geometryData);

	rString assetName = Id() + "_geometry";
	 m_geometry = m_engine->content->LoadGeometry(geometryData, assetName);

	m_geometryInvalid = false;
}

void rPrimitive::Draw(){
	if (m_geometryInvalid){
		RecreateGeometry();
	}

	rMaterial* material = m_engine->content->GetMaterialAsset("default_colored");
	if (material)
		material->SetColor("fragColor", m_color);

	rMatrix4 transform = TransformMatrix();
	m_engine->renderer->RenderGeometry(m_geometry, transform, "wire", material);
}