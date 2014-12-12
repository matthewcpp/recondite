#include "rSphereBoundingVolume.hpp"

bool rSphereBoundingVolume::IntersectsRay(const rRay3& ray) const{
	return rIntersection::RayIntersectsSphere(ray, m_sphere);
}

bool rSphereBoundingVolume::IntersectsRay(const rRay3& ray, rVector3* position) const{
	return rIntersection::RayIntersectsSphere(ray, m_sphere, position);
}

rAlignedBox3 rSphereBoundingVolume::FitBox() const{
	rAlignedBox3 b(m_sphere.center, m_sphere.center);

	rVector3 c(m_sphere.center.x + m_sphere.radius, m_sphere.center.y, m_sphere.center.z);
	b.AddPoint(c);

	c.Set(m_sphere.center.x - m_sphere.radius, m_sphere.center.y, m_sphere.center.z);
	b.AddPoint(c);

	c.Set(m_sphere.center.x, m_sphere.center.y + m_sphere.radius, m_sphere.center.z);
	b.AddPoint(c);

	c.Set(m_sphere.center.x, m_sphere.center.y - m_sphere.radius, m_sphere.center.z);
	b.AddPoint(c);

	c.Set(m_sphere.center.x, m_sphere.center.y, m_sphere.center.z + m_sphere.radius);
	b.AddPoint(c);

	c.Set(m_sphere.center.x, m_sphere.center.y, m_sphere.center.z - m_sphere.radius);
	b.AddPoint(c);

	return b;
}

void rSphereBoundingVolume::SetSphere(const rSphere& sphere){
	m_sphere = sphere;
}