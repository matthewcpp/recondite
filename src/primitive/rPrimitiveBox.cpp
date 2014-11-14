#include "primitive/rPrimitiveBox.hpp"

rPrimitiveBox::rPrimitiveBox(const rString& id, rEngine* engine)
	:rPrimitive(id, engine)
{
	m_width = 1.0f;
	m_height = 1.0f;
	m_depth = 1.0f;

	m_widthSegments = 3;
	m_heightSegments = 3;
	m_depthSegments = 3;


}

void rPrimitiveBox::GenerateFrontBack(float z){
	float stepX = m_width / (float)m_widthSegments;
	float stepY = m_height / (float)m_heightSegments;

	float halfWidth = m_width / 2.0f;
	float halfDepth = m_depth / 2.0f;

	float startX, startY;
	int widthCount = m_widthSegments + 1;
	int heightCount = m_heightSegments + 1;
	size_t baseIndex = geometry.VertexCount();
	startX = m_position.x - halfWidth;
	startY = m_position.y;

	for (int r = 0; r < heightCount; r++){
		float currentX = startX;
		float currentY = startY + m_height - ((float)r * stepY);

		for (int c = 0; c < widthCount; c++){
			int index = baseIndex + (r * widthCount) + c;

			geometry.PushVertex(currentX, currentY, z);

			if (c < m_widthSegments){
				geometry.PushIndex(index); geometry.PushIndex(index + 1);
			}

			if (r < m_heightSegments){
				geometry.PushIndex(index); geometry.PushIndex(index + widthCount);
			}

			currentX += stepX;
		}
	}
}

void rPrimitiveBox::GenerateTopBottom(float y){
	float stepX = m_width / (float)m_widthSegments;
	float stepZ = m_depth / (float)m_depthSegments;

	float halfWidth = m_width / 2.0f;
	float halfDepth = m_depth / 2.0f;

	float startX, startZ;
	int widthCount = m_widthSegments + 1;
	int depthCount = m_depthSegments + 1;
	size_t baseIndex = geometry.VertexCount();
	startX = m_position.x - halfWidth;
	startZ = m_position.z - halfDepth;

	for (int r = 0; r < depthCount; r++){
		float currentX = startX;
		float currentZ = startZ + ((float)r * stepZ);

		for (int c = 0; c < widthCount; c++){
			int index = baseIndex + (r * widthCount) + c;

			geometry.PushVertex(currentX, y, currentZ);

			if (c < m_widthSegments){
				geometry.PushIndex(index); geometry.PushIndex(index + 1);
			}

			if (r < m_depthSegments){
				geometry.PushIndex(index); geometry.PushIndex(index + widthCount);
			}

			currentX += stepX;
		}
	}
}

void rPrimitiveBox::GenerateLeftRight(float x){
	float stepY = m_height / (float)m_heightSegments;
	float stepZ = m_depth / (float)m_depthSegments;

	float halfDepth = m_depth / 2.0f;

	float startY, startZ;
	int depthCount = m_depthSegments + 1;
	int heightCount = m_heightSegments + 1;
	size_t baseIndex = geometry.VertexCount();
	startY = m_position.y + m_height;
	startZ = m_position.z - halfDepth;
	

	for (int r = 0; r < heightCount; r++){
		float currentZ = startZ;
		float currentY = startY - ((float)r * stepY);

		for (int c = 0; c < depthCount; c++){
			int index = baseIndex + (r * depthCount) + c;

			geometry.PushVertex(x, currentY, currentZ);

			if (c < m_depthSegments){
				geometry.PushIndex(index); geometry.PushIndex(index + 1);
			}

			if (r < m_heightSegments){
				geometry.PushIndex(index); geometry.PushIndex(index + depthCount);
			}

			currentZ += stepZ;
		}
	}
}

void rPrimitiveBox::CreateGeometry(){
	geometry.Reset(rGEOMETRY_LINES, 3, false);

	float halfWidth = m_width / 2.0f;
	float halfDepth = m_depth / 2.0f;

	
	GenerateFrontBack(m_position.z - halfDepth);	//generate back
	GenerateFrontBack(m_position.z + halfDepth);	//generate front

	GenerateTopBottom(m_position.y);				//generate bottom
	GenerateTopBottom(m_position.y + m_height);		//generate top

	GenerateLeftRight(m_position.x - halfWidth);	//generate left
	GenerateLeftRight(m_position.x + halfWidth);	//generate right
}



rString rPrimitiveBox::ClassName() const{
	return "PrimitiveBox";
}

float rPrimitiveBox::Width() const{
	return m_width;
}

void rPrimitiveBox::SetWidth(float width){
	m_width = width;
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