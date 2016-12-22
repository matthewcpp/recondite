#ifndef RI_BOUNDINGVOLUME_HPP
#define RI_BOUNDINGVOLUME_HPP

#include "rBuild.hpp"

#include "rLine3.hpp"
#include "rAlignedBox3.hpp"

#include "rPickResult.hpp"

class RECONDITE_API riBoundingVolume {
public:
	virtual ~riBoundingVolume() {}
	virtual bool IntersectsRay(const rRay3& ray, rPickResult& pickResult) const = 0;
	virtual rAlignedBox3 FitBox() const = 0;
};

#endif