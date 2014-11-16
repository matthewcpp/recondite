#include "primitive/rPrimitive.hpp"

rPrimitive::rPrimitive(const rString& id, rEngine* engine)
	:rActor3(id, engine)
{
	m_edgeColor = rColor(200, 200, 200, 255);
	m_faceColor = rColor::White;

	m_geometry = NULL;
	m_geometryInvalid = true;
}

rPrimitive::~rPrimitive(){
	if (m_geometry)
		m_engine->content->RemoveGeometryAsset(m_geometry->Name());
}

void rPrimitive::SetColor(const rColor& color){
	m_faceColor = color;
	m_edgeColor = rColor::White;
}

void rPrimitive::SetEdgeColor(const rColor& color){
	m_edgeColor = color;
}

void rPrimitive::SetFaceColor(const rColor& color){
	m_faceColor = color;
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
	if (!material) return;

	material->SetColor("fragColor", m_faceColor);
		
	rMatrix4 transform = TransformMatrix();
	m_engine->renderer->RenderShadedWithEdges(m_geometry, transform, material, m_edgeColor);
}