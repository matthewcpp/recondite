#include "primitive/rPrimitiveSphere.hpp"

rPrimitiveSphere::rPrimitiveSphere(const rString& id, rEngine* engine)
	:rPrimitive(id, engine)
{
	m_radius = 1.0f;
	m_rings = 15;
	m_sectors = 15;

	SetBoundingVolume(new rSphereBoundingVolume());
	RecalculateBoundingVolume();
}

float rPrimitiveSphere::Radius() const{
	return m_radius;
}

void rPrimitiveSphere::SetRadius(float radius){
	m_radius = radius;
	RecalculateBoundingVolume();
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

void rPrimitiveSphere::CreateGeometry(ModelData& modelData){
	rPrimitiveGeometry::rPrimitiveSphereParams params(m_radius, m_rings, m_sectors);
	rPrimitiveGeometry::CreateSphere(params, modelData);
}

void rPrimitiveSphere::RecalculateBoundingVolume(){
	rSphere s(0, m_radius, 0, m_radius);

	rSphereBoundingVolume* boundingVolume = (rSphereBoundingVolume*)BoundingVolume();
	boundingVolume->SetSphere(s);
}