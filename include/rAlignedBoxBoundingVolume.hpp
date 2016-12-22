#ifndef R_ALIGNEDBOXBOUNDINGVOLUME_HPP
#define R_ALIGNEDBOXBOUNDINGVOLUME_HPP

#include "rBuild.hpp"

#include "rLine3.hpp"
#include "rAlignedBox3.hpp"

#include "interface/riBoundingVolume.hpp"
#include "rIntersection.hpp"

class RECONDITE_API rAlignedBoxBoundingVolume : public riBoundingVolume{
public:
	void SetBox(rAlignedBox3& box);

	virtual bool IntersectsRay(const rRay3& ray, rPickResult& pickResult) const;
	virtual rAlignedBox3 FitBox() const;

private:
	rAlignedBox3 m_box;
};

#endif