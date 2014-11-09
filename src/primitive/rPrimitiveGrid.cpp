#include "primitive/rPrimitiveGrid.hpp"

rPrimitiveGrid::rPrimitiveGrid(const rString& id, rEngine* engine)
	:rPrimitive(id, engine)
{
	m_width = 1.0f;
	m_depth = 1.0f;

	m_rows = 1;
	m_columns = 1;
}

rString rPrimitiveGrid::ClassName() const{
	return "PrimitiveGrid";
}

void rPrimitiveGrid::CreateGeometry(){
	geometry.Reset(rGEOMETRY_LINES, 3, false);

	float startZ = -m_depth / 2.0f;
	float startX = -m_width / 2.0f;

	float columnWidth = m_width / (float)m_columns;
	float rowHeight = m_depth / (float)m_rows;

	for (int r = 0; r < m_rows; r++){
		float currentZ = startZ + ( rowHeight * (float)r );
		float currentX = startX;

		for (int c = 0; c < m_columns; c++){
			size_t index = geometry.VertexCount();

			if (c == 0){
				geometry.PushVertex(currentX, 0.0f, currentZ);
				geometry.PushVertex(currentX, 0.0f, currentZ + rowHeight);
				geometry.PushVertex(currentX + columnWidth, 0.0f, currentZ);
				geometry.PushVertex(currentX + columnWidth, 0.0f, currentZ + rowHeight);

				//wire indicies
				geometry.PushIndex(index, index + 2);
				geometry.PushIndex(index + 2, index + 3);
				geometry.PushIndex(index + 3, index + 1);
				geometry.PushIndex(index + 1, index);
			}
			else{
				geometry.PushVertex(currentX + columnWidth, 0.0f, currentZ);
				geometry.PushVertex(currentX + columnWidth, 0.0f, currentZ + rowHeight);

				//wire indicies
				geometry.PushIndex(index -2, index );
				geometry.PushIndex(index, index + 1);
				geometry.PushIndex(index - 1, index + 1);
			}

			currentX += columnWidth;
		}
	}
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