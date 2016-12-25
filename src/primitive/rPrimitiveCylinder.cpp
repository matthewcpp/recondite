#include "primitive/rPrimitiveCylinder.hpp"

rPrimitiveCylinder::rPrimitiveCylinder(const rString& id, rEngine* engine)
	:rPrimitive(id, engine)
{
	m_radius = 1.0f;
	m_height = 1.0f;
	m_segmentCount = 20;

	SetBoundingVolume(new rAlignedBoxBoundingVolume());
	RecalculateBoundingVolume();
}

bool rPrimitiveCylinder::DoSerialize(riSerializationTarget* target){
	target->Category(ClassName());

	target->Float("radius", m_radius);
	target->Float("height", m_height);

	target->Int("segmentCount", m_segmentCount);

	return rPrimitive::DoSerialize(target);
}

float rPrimitiveCylinder::Radius() const{
	return m_radius;
}

void rPrimitiveCylinder::SetRadius(float radius){
	m_radius = radius;
	RecalculateBoundingVolume();
	InvalidateGeometry();
}

float rPrimitiveCylinder::Height() const{
	return m_height;
}

void rPrimitiveCylinder::SetHeight(float height){
	m_height = height;
	RecalculateBoundingVolume();
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

void rPrimitiveCylinder::CreateGeometry(ModelData& modelData){
	rPrimitiveGeometry::rPrimitiveCylinderParams params(m_radius, m_height, m_segmentCount);
	rPrimitiveGeometry::CreateCylinder(params, modelData);
}

void AddCircle(const rVector3& center, float radius, rAlignedBox3& b){
	rVector3 pt = center + (rVector3::ForwardVector * radius);
	b.AddPoint(pt);

	pt = center + (rVector3::BackwardVector * radius);
	b.AddPoint(pt);

	pt = center + (rVector3::LeftVector * radius);
	b.AddPoint(pt);

	pt = center + (rVector3::RightVector * radius);
	b.AddPoint(pt);
}

void rPrimitiveCylinder::RecalculateBoundingVolume(){
	rAlignedBox3 b;

	AddCircle(rVector3::ZeroVector, m_radius, b);
	AddCircle(rVector3::UpVector * m_height, m_radius, b);

	rAlignedBoxBoundingVolume* boundingVolume = (rAlignedBoxBoundingVolume*)BoundingVolume();
	boundingVolume->SetBox(b);
}
