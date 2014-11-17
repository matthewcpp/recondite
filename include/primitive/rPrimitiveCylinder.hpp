#ifndef R_PRIMITIVECYLINDER_HPP
#define R_PRIMITIVECYLINDER_HPP

#include "rBuild.hpp"

#include "primitive/rPrimitive.hpp"

class RECONDITE_API rPrimitiveCylinder : public rPrimitive{
public:
	rPrimitiveCylinder(const rString& id, rEngine* engine);

public:
	float Radius() const;
	void SetRadius(float radius);

	float Height() const;
	void SetHeight(float height);

	int SegmentCount() const;
	void SetSegmentCount(int segmentCount);

	virtual rString ClassName() const;

protected:
	virtual void CreateGeometry(rGeometryData& geometry);

private:
	void CreateCircle3d(rGeometryData& geometry, const rVector3& normal, const rVector3& center);
	void CreateShellFace(rGeometryData& geometry, int i1, int i2, int i3, int i4);

private:
	float m_radius;
	float m_height;

	int m_segmentCount;
};

#endif