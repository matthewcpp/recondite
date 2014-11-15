#include "primitive/rPrimitiveSphere.hpp"

rPrimitiveSphere::rPrimitiveSphere(const rString& id, rEngine* engine)
	:rPrimitive(id, engine)
{
	m_radius = 1.0f;
	m_rings = 15;
	m_sectors = 15;
}

float rPrimitiveSphere::Radius() const{
	return m_radius;
}

void rPrimitiveSphere::SetRadius(float radius){
	m_radius = radius;
	InvalidateGeometry();
}

int rPrimitiveSphere::Rings() const{
	return m_rings;
}

void rPrimitiveSphere::SetRings(int rings){
	m_rings = rings;
	InvalidateGeometry();
}

int rPrimitiveSphere::Sectors() const{
	return m_sectors;
}

void rPrimitiveSphere::SetSectors(int sectors){
	m_sectors = sectors;
	InvalidateGeometry();
}

rString rPrimitiveSphere::ClassName() const{
	return "PrimitiveSphere";
}

void rPrimitiveSphere::CreateGeometry(rGeometryData& geometry){
	rElementBufferData* wireframe = geometry.CreateElementBuffer("wire", rGEOMETRY_LINES);
	rElementBufferData* shaded = geometry.CreateElementBuffer("shaded", rGEOMETRY_TRIANGLES);

	rVector3 position = rVector3::ZeroVector;
	rVector3 normal = rVector3::ZeroVector;
	rVector2 texCoord = rVector2::ZeroVector;

	float R = 1.0f / (float)(m_rings-1);
    float S = 1.0f / (float)(m_sectors-1);
    int r, s;

	for(r = 0; r < m_rings; r++){
		for(s = 0; s < m_sectors; s++) {
			float y = std::sin( -M_PI_2 + M_PI * r * R );
			float x = std::cos(2*M_PI * s * S) * std::sin( M_PI * r * R );
			float z = std::sin(2*M_PI * s * S) * std::sin( M_PI * r * R );

			position.Set(x * m_radius, (y * m_radius) + m_radius, z * m_radius);
			geometry.PushVertex(position, normal, texCoord);
		}
	}

	//generate indicies
	for(r = 0; r < m_rings-1; r++) {
		for(s = 0; s < m_sectors-1; s++) {
                int p1 = r * m_sectors + s;
                int p2 = r * m_sectors + (s+1);
                int p3 = (r+1) * m_sectors + (s+1);
                int p4 = (r+1) * m_sectors + s;

				//lines
				wireframe->Push(p1,p2);
				wireframe->Push(p2,p3);
				wireframe->Push(p3,p4);
				wireframe->Push(p4,p1);
		}
	}
}