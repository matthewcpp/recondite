#include "primitive/rPrimitiveBox.hpp"

rPrimitiveBox::rPrimitiveBox(const rString& id, rEngine* engine)
	:rPrimitive(id, engine)
{
	m_width = 1.0f;
	m_height = 1.0f;
	m_depth = 1.0f;

	m_widthSegments = 1;
	m_heightSegments = 1;
	m_depthSegments = 1;

	SetBoundingVolume(new rAlignedBoxBoundingVolume());
	RecalculateBoundingVolume();
}

void rPrimitiveBox::CreateGeometry(ModelData& modelData){
	rPrimitiveGeometry::rPrimitiveBoxParams params(rVector3(m_width, m_height, m_depth), m_widthSegments, m_heightSegments, m_depthSegments);
	rPrimitiveGeometry::CreateBox(params, modelData);
}

rString rPrimitiveBox::ClassName() const{
	return "PrimitiveBox";
}

float rPrimitiveBox::Width() const{
	return m_width;
}

void rPrimitiveBox::SetWidth(float width){
	m_width = width;
	RecalculateBoundingVolume();
	InvalidateGeometry();
}

int rPrimitiveBox::WidthSegments() const{
	return m_widthSegments;
}

void rPrimitiveBox::SetWidthSegments(int widthSegments){
	m_widthSegments = widthSegments;
	InvalidateGeometry();
}

float rPrimitiveBox::Height() const{
	return m_height;
}

void rPrimitiveBox::SetHeight(float height){
	m_height = height;
	RecalculateBoundingVolume();
	InvalidateGeometry();
}

int rPrimitiveBox::HeightSegments() const{
	return m_heightSegments;
}

void rPrimitiveBox::SetHeightSegments(int heightSegments){
	m_heightSegments = heightSegments;
	InvalidateGeometry();
}

float rPrimitiveBox::Depth() const{
	return m_depth;
}

void rPrimitiveBox::SetDepth(float depth){
	m_depth = depth;
	InvalidateGeometry();
}

int rPrimitiveBox::DepthSegments() const{
	return m_depthSegments;
}

void rPrimitiveBox::SetDepthSegments(int depthSegments){
	m_depthSegments = depthSegments;
	InvalidateGeometry();
}


void rPrimitiveBox::RecalculateBoundingVolume(){
	float halfWidth = m_width / 2.0f;
	float halfDepth = m_depth / 2.0f;
	
	rVector3 pt;
	rAlignedBox3 b;

	pt.Set(-halfWidth, m_height, halfDepth);
	b.min = pt;	b.max = pt;

	pt.Set(halfWidth, m_height, halfDepth);
	b.AddPoint(pt);

	pt.Set(halfWidth, 0, halfDepth);
	b.AddPoint(pt);

	pt.Set(-halfWidth, 0, halfDepth);
	b.AddPoint(pt);

	pt.Set(-halfWidth, m_height, -halfDepth);
	b.AddPoint(pt);

	pt.Set(halfWidth, m_height, -halfDepth);
	b.AddPoint(pt);

	pt.Set(halfWidth, 0, -halfDepth);
	b.AddPoint(pt);

	pt.Set(-halfWidth, 0, -halfDepth);
	b.AddPoint(pt);

	rAlignedBoxBoundingVolume* boundingVolume = (rAlignedBoxBoundingVolume*)BoundingVolume();
	boundingVolume->SetBox(b);
}

bool rPrimitiveBox::DoSerialize(riSerializationTarget* target, rSerializeAction action){
	target->Category(ClassName());

	target->Float("width", m_width);
	target->Float("height", m_height);
	target->Float("depth", m_depth);

	target->Int("widthSegments", m_widthSegments);
	target->Int("heightSegments", m_heightSegments);
	target->Int("depthSegments", m_depthSegments);

	return rPrimitive::DoSerialize(target, action);
}