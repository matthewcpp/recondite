#include "primitive/rPrimitiveCone.hpp"

rPrimitiveCone::rPrimitiveCone(const rString& id, rEngine* engine)
	:rPrimitive(id, engine)
{
	m_height = 2.0f;
	m_radius = 1.0f;
	
	m_segmentCount = 15;
}

float rPrimitiveCone::Radius() const{
	return m_radius;
}

void rPrimitiveCone::SetRadius(float radius){
	m_radius = radius;
	InvalidateGeometry();
}

float rPrimitiveCone::Height() const{
	return m_height;
}

void rPrimitiveCone::SetHeight(float height){
	m_height = height;
	InvalidateGeometry();
}

rString rPrimitiveCone::ClassName() const{
	return "PrimitiveCone";
}

void rPrimitiveCone::CreateGeometry(rModelGeometryData& geometry){
	rPrimitiveGeometry::CreateCone(m_radius, m_height, m_segmentCount, geometry);
}

int rPrimitiveCone::SegmentCount() const{
	return m_segmentCount;
}

void rPrimitiveCone::SetSegmentCount(int segmentCount){
	m_segmentCount = segmentCount;
	InvalidateGeometry();
}

bool rPrimitiveCone::DoSerialize(riSerializationTarget* target){
	target->Category(ClassName());

	target->Float("radius", m_radius);
	target->Float("height", m_height);

	target->Int("segmentCount", m_segmentCount);

	return rPrimitive::DoSerialize(target);
}