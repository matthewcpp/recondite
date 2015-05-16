#include "primitive/rPrimitive.hpp"

rPrimitive::rPrimitive(const rString& id, rEngine* engine)
	:rActor3(id, engine)
{
	m_edgeColor = rColor(200, 200, 200, 255);
	m_faceColor = rColor::White;

	m_geometry = NULL;
	m_geometryInvalid = true;

	m_drawable.reset(new rDrawable());
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

	rTexCoordGeometryData geometryData;
	CreateGeometry(geometryData);

	rString assetName = Id() + "_geometry";
	 m_geometry = m_engine->content->LoadGeometry(geometryData, assetName);

	m_geometryInvalid = false;
}

void rPrimitive::OnDelete(){
	if (m_geometry)
		m_engine->content->RemoveGeometryAsset(m_geometry->Name());
}

void rPrimitive::Draw(){
	if (m_geometryInvalid){
		RecreateGeometry();
	}

	rMaterial* material = m_engine->content->GetMaterialAsset("default_colored");
	if (!material) return;

	material->SetColor("fragColor", m_faceColor);
		
	rMatrix4& transform = TransformMatrix();
	rRenderMode renderMode = m_drawable->RenderMode();

	switch (renderMode){
		case rRenderMode::Shaded:
			material->SetColor("fragColor", m_edgeColor);
			m_engine->renderer->RenderGeometry(m_geometry, transform, "wire", material);
			break;

		case rRenderMode::Wireframe:
			material->SetColor("fragColor", m_edgeColor);
			m_engine->renderer->RenderGeometry(m_geometry, transform, "wire", material);
			break;

		case rRenderMode::Default:
		case rRenderMode::WireframeOnShaded:
			material->SetColor("fragColor", m_faceColor);
			m_engine->renderer->RenderShadedWithEdges(m_geometry, transform, material, m_edgeColor);
			break;
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