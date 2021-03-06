#ifndef R_PRIMITIVECYLINDER_HPP
#define R_PRIMITIVECYLINDER_HPP

#include "rBuild.hpp"

#include "primitive/rPrimitive.hpp"
#include "rPrimitiveGeometry.hpp"

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
	virtual void CreateGeometry(ModelData& modelData) override;

	virtual void RecalculateBoundingVolume() override;
	bool DoSerialize(riSerializationTarget* target, rSerializeAction action) override;

private:
	float m_radius;
	float m_height;

	int m_segmentCount;
};

#endif