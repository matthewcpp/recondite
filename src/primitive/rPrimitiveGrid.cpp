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

void rPrimitiveGrid::CreateGeometry(rModelGeometryData& geometry){
	rElementBufferData* wireframe = geometry.CreateElementBuffer("wire", rGEOMETRY_LINES);
	rElementBufferData* shaded = geometry.CreateElementBuffer("shaded", rGEOMETRY_TRIANGLES);

	float stepX = m_width / (float)m_columns;
	float stepZ = m_depth / (float)m_rows;

	rVector3 vertex;
	rVector2 texCoord = rVector2::ZeroVector;
	rVector3 normal = rVector3::UpVector;

	float halfWidth = m_width / 2.0f;
	float halfDepth = m_depth / 2.0f;

	float startX, startZ;
	int widthCount = m_columns + 1;
	int depthCount = m_rows + 1;
	size_t baseIndex = geometry.VertexCount();
	startX = -halfWidth;
	startZ = -halfDepth;

	for (int r = 0; r < depthCount; r++){
		float currentX = startX;
		float currentZ = startZ + ((float)r * stepZ);

		for (int c = 0; c < widthCount; c++){
			int index = baseIndex + (r * widthCount) + c;

			vertex.Set(currentX, 0.0f, currentZ);
			geometry.PushVertex(vertex, normal, texCoord);

			if (c < m_columns)
				wireframe->Push(index, index + 1);

			if (r < m_rows)
				wireframe->Push(index, index + widthCount);

			currentX += stepX;
		}
	}

	shaded->Push(0, m_columns, m_rows * widthCount);
	shaded->Push(m_columns, m_rows * widthCount, geometry.VertexCount() - 1);
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