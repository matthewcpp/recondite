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
}

int rPrimitiveSphere::Rings() const{
	return m_rings;
}

void rPrimitiveSphere::SetRings(int rings){
	m_rings = rings;
}

int rPrimitiveSphere::Sectors() const{
	return m_sectors;
}

void rPrimitiveSphere::SetSectors(int sectors){
	m_sectors = sectors;
}

rString rPrimitiveSphere::ClassName() const{
	return "PrimitiveSphere";
}

void rPrimitiveSphere::CreateGeometry(){
	geometry.Reset(rGEOMETRY_LINES, 3, false);

	float R = 1.0f / (float)(m_rings-1);
    float S = 1.0f / (float)(m_sectors-1);
    int r, s;

	for(r = 0; r < m_rings; r++){
		for(s = 0; s < m_sectors; s++) {
			float y = std::sin( -M_PI_2 + M_PI * r * R );
			float x = std::cos(2*M_PI * s * S) * std::sin( M_PI * r * R );
			float z = std::sin(2*M_PI * s * S) * std::sin( M_PI * r * R );

			geometry.PushVertex(x * m_radius , (y * m_radius) + m_radius,z * m_radius);
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
				geometry.PushIndex(p1,p2);
				geometry.PushIndex(p2,p3);
				geometry.PushIndex(p3,p4);
				geometry.PushIndex(p4,p1);
		}
	}
}