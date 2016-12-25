#include "primitive/rPrimitiveGrid.hpp"

rPrimitiveGrid::rPrimitiveGrid(const rString& id, rEngine* engine)
	:rPrimitive(id, engine)
{
	m_width = 1.0f;
	m_depth = 1.0f;

	m_rows = 1;
	m_columns = 1;

	SetBoundingVolume(new rAlignedBoxBoundingVolume());
	RecalculateBoundingVolume();
}

rString rPrimitiveGrid::ClassName() const{
	return "PrimitiveGrid";
}

void rPrimitiveGrid::CreateGeometry(ModelData& modelData){
	rPrimitiveGeometry::rPrimitiveGridParams params(m_width, m_depth, m_rows, m_columns);
	rPrimitiveGeometry::CreateGrid(params, modelData);
}

float rPrimitiveGrid::Width() const{
	return m_width;
}

void rPrimitiveGrid::SetWidth(float width){
	m_width = width;
	InvalidateGeometry();
}

float rPrimitiveGrid::Depth() const{
	return m_depth;
}

void rPrimitiveGrid::SetDepth(float depth){
	m_depth = depth;
	InvalidateGeometry();
}

int rPrimitiveGrid::Rows() const{
	return m_rows;
}

void rPrimitiveGrid::SetRows(int rows){
	m_rows = std::max(rows, 1);
	InvalidateGeometry();
}

int rPrimitiveGrid::Colums() const{
	return m_columns;
}

void rPrimitiveGrid::SetColumns( int columns){
	m_columns = std::max(columns, 1);
	InvalidateGeometry();
}

bool rPrimitiveGrid::DoSerialize(riSerializationTarget* target){
	target->Category(ClassName());

	target->Float("width", m_width);
	target->Float("depth", m_depth);

	target->Int("rows", m_rows);
	target->Int("columns", m_columns);

	return rPrimitive::DoSerialize(target);
}

void rPrimitiveGrid::RecalculateBoundingVolume(){
	float halfWidth = m_width / 2.0f;
	float halfDepth = m_depth / 2.0f;

	rVector3 pt;
	rAlignedBox3 b;

	pt.Set(-halfWidth, 0, halfDepth);
	b.AddPoint(pt);

	pt.Set(halfWidth, 0, halfDepth);
	b.AddPoint(pt);

	pt.Set(halfWidth, 0, -halfDepth);
	b.AddPoint(pt);

	pt.Set(-halfWidth, 0, -halfDepth);
	b.AddPoint(pt);

	rAlignedBoxBoundingVolume* boundingVolume = (rAlignedBoxBoundingVolume*)BoundingVolume();
	boundingVolume->SetBox(b);
}