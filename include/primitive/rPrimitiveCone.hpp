#ifndef R_PRIMITIVECONE_HPP
#define R_PRIMITIVECONE_HPP

#include "rBuild.hpp"

#include "primitive/rPrimitive.hpp"
#include "primitive/rPrimitiveGeometry.hpp"

class RECONDITE_API rPrimitiveCone : public rPrimitive{
public:
	rPrimitiveCone(const rString& id, rEngine* engine);

	float Radius() const;
	void SetRadius(float radius);

	float Height() const;
	void SetHeight(float height);

	int SegmentCount() const;
	void SetSegmentCount(int segmentCount);

	virtual rString ClassName() const;

protected:
	virtual void CreateGeometry(ModelData& modelData) override;
	virtual bool DoSerialize(riSerializationTarget* target) override;

	virtual void DoRecalculateBoundingVolume() override;
	virtual riBoundingVolume* DoGetBoundingVolume()override;

private:
	rAlignedBoxBoundingVolume m_boundingVolume;

	float m_height;
	float m_radius;

	int m_segmentCount;
};

#endif