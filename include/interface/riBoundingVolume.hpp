#ifndef RI_BOUNDINGVOLUME_HPP
#define RI_BOUNDINGVOLUME_HPP

#include "rBuild.hpp"

#include "rLine3.hpp"

class RECONDITE_API riBoundingVolume {
public:
	virtual bool IntersectsRay(const rRay3& ray) const = 0;
	virtual bool IntersectsRay(const rRay3& ray, rVector3* position) const = 0;
	virtual rAlignedBox3 FitBox() const = 0;
};

#endif