#include "primitive/rPrimitiveCylinder.hpp"

rPrimitiveCylinder::rPrimitiveCylinder(const rString& id, rEngine* engine)
	:rPrimitive(id, engine)
{
	m_radius = 1.0f;
	m_height = 1.0f;
	m_segmentCount = 20;
}

float rPrimitiveCylinder::Radius() const{
	return m_radius;
}

void rPrimitiveCylinder::SetRadius(float radius){
	m_radius = radius;
	InvalidateGeometry();
}

float rPrimitiveCylinder::Height() const{
	return m_height;
}

void rPrimitiveCylinder::SetHeight(float height){
	m_height = height;
	InvalidateGeometry();
}

rString rPrimitiveCylinder::ClassName() const{
	return "PrimitiveCylinder";
}

int rPrimitiveCylinder::SegmentCount() const{
	return m_segmentCount;
}

void rPrimitiveCylinder::SetSegmentCount(int segmentCount){
	m_segmentCount = segmentCount;
	InvalidateGeometry();
}

void rPrimitiveCylinder::CreateCircle3d(rGeometryData& geometry, const rVector3& normal, const rVector3& center){
	rElementBufferData* wireframe = geometry.GetElementBuffer("wire");
	rElementBufferData* shaded = geometry.GetElementBuffer("shaded");

	float step = 360.0f / (float)m_segmentCount;

	rVector3 position;
	rVector2 texCoord = rVector2::ZeroVector;

	size_t baseIndex = geometry.VertexCount();
	geometry.PushVertex(center, normal, texCoord);

	for (int i = 0; i < m_segmentCount; i++){
		float angle = float(i) * step;
		float radians = rMath::DegreeToRad(angle);
		
		position.Set(std::cos(radians), 0.0f, std::sin(radians));
		position *= m_radius;
		position += center;
		
		geometry.PushVertex(position, normal, texCoord);

		if (i > 0){
			wireframe->Push(baseIndex + i, baseIndex + i + 1);
			shaded->Push(baseIndex, baseIndex + i,  baseIndex + i + 1);
		}
	}

	wireframe->Push(baseIndex + m_segmentCount, baseIndex + 1);
	shaded->Push(baseIndex, baseIndex + m_segmentCount,  baseIndex + 1);
}

void rPrimitiveCylinder::CreateGeometry(rGeometryData& geometry){
	rElementBufferData* wireframe = geometry.CreateElementBuffer("wire", rGEOMETRY_LINES);
	rElementBufferData* shaded = geometry.CreateElementBuffer("shaded", rGEOMETRY_TRIANGLES);

	CreateCircle3d(geometry, rVector3::UpVector, rVector3::ZeroVector);
	CreateCircle3d(geometry, rVector3::UpVector, rVector3::UpVector * m_height);

	for (int i = 1; i <= m_segmentCount; i++){
		wireframe->Push(i , i + m_segmentCount + 1);

		if (i > 1) CreateShellFace(geometry,i -1, i, i + m_segmentCount, i + m_segmentCount + 1);
	}

	CreateShellFace(geometry,m_segmentCount, 2 * m_segmentCount + 1, 1, m_segmentCount + 2);
}

void rPrimitiveCylinder::CreateShellFace(rGeometryData& geometry, int i1, int i2, int i3, int i4){
	rElementBufferData* shaded = geometry.GetElementBuffer("shaded");

		rVector3 v1, v2, v3, v4, n1, n2, n3, n4;
		size_t baseIndex = geometry.VertexCount();

		geometry.GetVertex(i1, &v1, NULL, NULL);
		n1 = v1;

		geometry.GetVertex(i2, &v2, NULL, NULL);
		n2 = v2;

		geometry.GetVertex(i3, &v3, NULL, NULL);
		n3 = v3;

		geometry.GetVertex(i4, &v4, NULL, NULL);
		n4 = v4;

		geometry.PushVertex(v1,n1,rVector2::ZeroVector);
		geometry.PushVertex(v2,n2,rVector2::ZeroVector);
		geometry.PushVertex(v3,n3,rVector2::ZeroVector);
		geometry.PushVertex(v4,n4,rVector2::ZeroVector);

		shaded->Push(baseIndex, baseIndex + 2, baseIndex + 3);
		shaded->Push(baseIndex, baseIndex + 1, baseIndex + 3);
}