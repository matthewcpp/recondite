#ifndef R_PRIMITIVEBOX_HPP
#define R_PRIMITIVEBOX_HPP

#include "rBuild.hpp"
#include "rAlignedBox3.hpp"

#include "primitive/rPrimitive.hpp"

class RECONDITE_API rPrimitiveBox : public rPrimitive{
public:
	rPrimitiveBox(const rString& id, rEngine* engine);

public:

	virtual rString ClassName() const;

	float Width() const;
	void SetWidth(float width);

	int WidthSegments() const;
	void SetWidthSegments(int widthSegments);

	float Height() const;
	void SetHeight(float height);

	int HeightSegments() const;
	void SetHeightSegments(int heightSegments);

	float Depth() const;
	void SetDepth(float depth);

	int DepthSegments() const;
	void SetDepthSegments(int depthSegments);

protected:
	virtual bool DoSerialize(riSerializationTarget* target);

	virtual void CreateGeometry(rModelGeometryData& geometry);
	virtual void DoRecalculateBoundingVolume();
	virtual riBoundingVolume* DoGetBoundingVolume();

	void GenerateFrontBack(rModelGeometryData& geometry, float z, const rVector3& normal);
	void GenerateTopBottom(rModelGeometryData& geometry, float y, const rVector3& normal);
	void GenerateLeftRight(rModelGeometryData& geometry, float x, const rVector3& nomral);

private:

	float m_width;
	float m_height;
	float m_depth;

	int m_widthSegments;
	int m_heightSegments;
	int m_depthSegments;

	rAlignedBoxBoundingVolume m_boundingVolume;
};

#endif