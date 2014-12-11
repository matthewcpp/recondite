#include "rAlignedBoxBoundingVolume.hpp"

void rAlignedBoxBoundingVolume::SetBox(rAlignedBox3& box){
	m_box = box;
}

bool rAlignedBoxBoundingVolume::IntersectsRay(const rRay3& ray) const{
	return rIntersection::RayIntersectsAlignedBox(ray, m_box);
}

bool rAlignedBoxBoundingVolume::IntersectsRay(const rRay3& ray, rVector3* position) const{
	return rIntersection::RayIntersectsAlignedBox(ray, m_box, position);
}

rAlignedBox3 rAlignedBoxBoundingVolume::FitBox() const{
	return m_box;
}