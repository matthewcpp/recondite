#ifndef R_PRIMITIVESPHERE_HPP
#define R_PRIMITIVESPHERE_HPP

#include <map>
#include <vector>

#include "rBuild.hpp"
#include "rMathUtil.hpp"

#include "primitive/rPrimitive.hpp"
#include "rSphereBoundingVolume.hpp"

class RECONDITE_API rPrimitiveSphere : public rPrimitive{
public:
	rPrimitiveSphere(const rString& id, rEngine* engine);

public:

	float Radius() const;
	void SetRadius(float radius);

	int Rings() const;
	void SetRings(int rings);

	int Sectors() const;
	void SetSectors(int sectors);

	virtual rString ClassName() const;


protected:
	virtual void CreateGeometry(rModelGeometryData& geometry);
	virtual void DoRecalculateBoundingVolume();
	virtual riBoundingVolume* DoGetBoundingVolume();

private:
	float m_radius;
	int m_rings;
	int m_sectors;

	rSphereBoundingVolume m_boundingVolume;
};

#endif