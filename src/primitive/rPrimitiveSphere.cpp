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

void rPrimitiveSphere::CreateGeometry(rTexCoordGeometryData& geometry){
	rPrimitiveGeometry::CreateSphere(m_radius, m_rings, m_sectors, geometry);
}

riBoundingVolume* rPrimitiveSphere::DoGetBoundingVolume(){
	return &m_boundingVolume;
}

void rPrimitiveSphere::DoRecalculateBoundingVolume(){
	rMatrix4 transform = TransformMatrix();

	//todo: handle non uniform scale for sphere?
	float sphereRadius = m_scale.x * m_radius;
	rSphere s(m_position.x, m_position.y + sphereRadius, m_position.z, sphereRadius);

	m_boundingVolume.SetSphere(s);
}