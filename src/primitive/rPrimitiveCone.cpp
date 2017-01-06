#include "primitive/rPrimitiveCone.hpp"

rPrimitiveCone::rPrimitiveCone(const rString& id, rEngine* engine)
	:rPrimitive(id, engine)
{
	m_height = 2.0f;
	m_radius = 1.0f;
	
	m_segmentCount = 15;

	SetBoundingVolume(new rAlignedBoxBoundingVolume());
	RecalculateBoundingVolume();
}

float rPrimitiveCone::Radius() const{
	return m_radius;
}

void rPrimitiveCone::SetRadius(float radius){
	m_radius = radius;
	RecalculateBoundingVolume();
	InvalidateGeometry();
}

float rPrimitiveCone::Height() const{
	return m_height;
}

void rPrimitiveCone::SetHeight(float height){
	m_height = height;
	RecalculateBoundingVolume();
	InvalidateGeometry();
}

rString rPrimitiveCone::ClassName() const{
	return "PrimitiveCone";
}

void rPrimitiveCone::CreateGeometry(ModelData& modelData){
	rPrimitiveGeometry::rPrimitiveConeParams params(m_radius, m_height, m_segmentCount);
	rPrimitiveGeometry::CreateCone(params, modelData);
}

int rPrimitiveCone::SegmentCount() const{
	return m_segmentCount;
}

void rPrimitiveCone::SetSegmentCount(int segmentCount){
	m_segmentCount = segmentCount;
	InvalidateGeometry();
}

bool rPrimitiveCone::DoSerialize(riSerializationTarget* target, rSerializeAction action){
	target->Category(ClassName());

	target->Float("radius", m_radius);
	target->Float("height", m_height);

	target->Int("segmentCount", m_segmentCount);

	return rPrimitive::DoSerialize(target, action);
}

void rPrimitiveCone::RecalculateBoundingVolume(){
	rAlignedBox3 b;
	rVector3 pt = rVector3::ForwardVector * m_radius;
	b.AddPoint(pt);

	pt = rVector3::BackwardVector * m_radius;
	b.AddPoint(pt);

	pt = rVector3::LeftVector * m_radius;
	b.AddPoint(pt);

	pt = rVector3::RightVector * m_radius;
	b.AddPoint(pt);

	pt = rVector3::UpVector * m_height;
	b.AddPoint(pt);

	rAlignedBoxBoundingVolume* boundingVolume = (rAlignedBoxBoundingVolume*)BoundingVolume();
	boundingVolume->SetBox(b);
}