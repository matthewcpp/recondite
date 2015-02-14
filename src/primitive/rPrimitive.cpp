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

void rPrimitive::CreateCircle3d(rGeometryData& geometry, const rVector3& center, float radius, const rVector3& normal, int segmentCount){
	rElementBufferData* wireframe = geometry.GetElementBuffer("wire");
	rElementBufferData* shaded = geometry.GetElementBuffer("shaded");

	float step = 360.0f / (float)segmentCount;

	rVector3 position;
	rVector2 texCoord = rVector2::ZeroVector;

	size_t baseIndex = geometry.VertexCount();
	geometry.PushVertex(center, normal, texCoord);

	for (int i = 0; i < segmentCount; i++){
		float angle = float(i) * step;
		float radians = rMath::DegreeToRad(angle);
		
		position.Set(std::cos(radians), 0.0f, std::sin(radians));
		position *= radius;
		position += center;
		
		geometry.PushVertex(position, normal, texCoord);

		if (i > 0){
			wireframe->Push(baseIndex + i, baseIndex + i + 1);
			shaded->Push(baseIndex, baseIndex + i,  baseIndex + i + 1);
		}
	}

	wireframe->Push(baseIndex + segmentCount, baseIndex + 1);
	shaded->Push(baseIndex, baseIndex + segmentCount,  baseIndex + 1);
}

rColor rPrimitive::EdgeColor() const{
	return m_edgeColor;
}

rColor rPrimitive::FaceColor() const{
	return m_faceColor;
}

bool rPrimitive::DoSerialize(riSerializationTarget* target){
	target->SetColorProperty("faceColor", m_faceColor);
	target->SetColorProperty("edgeColor", m_edgeColor);

	return rActor3::DoSerialize(target);
}