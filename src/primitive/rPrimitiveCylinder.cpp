#include "primitive/rPrimitiveCylinder.hpp"

rPrimitiveCylinder::rPrimitiveCylinder(const rString& id, rEngine* engine)
	:rPrimitive(id, engine)
{
	m_radius = 1.0f;
	m_height = 1.0f;
	m_segmentCount = 20;
}

float rPrimitiveCylinder::Radius() const{
	return m_radius;
}

void rPrimitiveCylinder::SetRadius(float radius){
	m_radius = radius;
	InvalidateGeometry();
}

float rPrimitiveCylinder::Height() const{
	return m_height;
}

void rPrimitiveCylinder::SetHeight(float height){
	m_height = height;
	InvalidateGeometry();
}

rString rPrimitiveCylinder::ClassName() const{
	return "PrimitiveCylinder";
}

int rPrimitiveCylinder::SegmentCount() const{
	return m_segmentCount;
}

void rPrimitiveCylinder::SetSegmentCount(int segmentCount){
	m_segmentCount = segmentCount;
	InvalidateGeometry();
}

void rPrimitiveCylinder::CreateGeometry(rTexCoordGeometryData& geometry){
	rPrimitiveGeometry::CreateCylinder(m_radius, m_height, m_segmentCount, geometry);
}

riBoundingVolume* rPrimitiveCylinder::DoGetBoundingVolume(){
	return &m_boundingVolume;
}

void AddCircle(const rVector3& center, float radius, const rMatrix4& transform, rAlignedBox3& b){
	rVector3 pt = center + (rVector3::ForwardVector * radius);
	transform.TransformVector3(pt);
	b.AddPoint(pt);

	pt = center + (rVector3::BackwardVector * radius);
	transform.TransformVector3(pt);
	b.AddPoint(pt);

	pt = center + (rVector3::LeftVector * radius);
	transform.TransformVector3(pt);
	b.AddPoint(pt);

	pt = center + (rVector3::RightVector * radius);
	transform.TransformVector3(pt);
	b.AddPoint(pt);
}

void rPrimitiveCylinder::DoRecalculateBoundingVolume(){
	rMatrix4 transform = TransformMatrix();

	rAlignedBox3 b;

	AddCircle(rVector3::ZeroVector, m_radius, transform, b);
	AddCircle(rVector3::UpVector * m_height, m_radius, transform, b);

	m_boundingVolume.SetBox(b);
}
