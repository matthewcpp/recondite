#include "rAlignedBoxBoundingVolume.hpp"

void rAlignedBoxBoundingVolume::SetBox(rAlignedBox3& box){
	m_box = box;
}

bool rAlignedBoxBoundingVolume::IntersectsRay(const rRay3& ray, rPickResult& pickResult) const{
	pickResult.hit = rIntersection::RayIntersectsAlignedBox(ray, m_box, &pickResult.point);

	return pickResult.hit;
}

rAlignedBox3 rAlignedBoxBoundingVolume::FitBox() const{
	return m_box;
}