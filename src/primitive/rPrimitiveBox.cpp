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

void rPrimitiveBox::GenerateFrontBack(rGeometryData& geometry, float z, const rVector3& normal){
	float stepX = m_width / (float)m_widthSegments;
	float stepY = m_height / (float)m_heightSegments;

	rVector3 vertex;
	rVector2 texCoord = rVector2::ZeroVector;

	rElementBufferData* wireframe = geometry.GetElementBuffer("wire");
	rElementBufferData* shaded = geometry.GetElementBuffer("shaded");

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

			vertex.Set(currentX, currentY, z);
			geometry.PushVertex(vertex, normal, texCoord);

			if (c < m_widthSegments){
				wireframe->Push(index, index + 1);
			}

			if (r < m_heightSegments){
				wireframe->Push(index, index + widthCount);
			}

			currentX += stepX;
		}
	}

	shaded->Push(baseIndex, baseIndex + m_widthSegments, baseIndex + m_heightSegments * widthCount);
	shaded->Push(baseIndex + m_widthSegments, baseIndex + m_heightSegments * widthCount, geometry.VertexCount() - 1);
}

void rPrimitiveBox::GenerateTopBottom(rGeometryData& geometry, float y, const rVector3& normal){
	float stepX = m_width / (float)m_widthSegments;
	float stepZ = m_depth / (float)m_depthSegments;

	rVector3 vertex;
	rVector2 texCoord = rVector2::ZeroVector;

	rElementBufferData* wireframe = geometry.GetElementBuffer("wire");
	rElementBufferData* shaded = geometry.GetElementBuffer("shaded");

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

			vertex.Set(currentX, y, currentZ);
			geometry.PushVertex(vertex, normal, texCoord);

			if (c < m_widthSegments){
				wireframe->Push(index, index + 1);
			}

			if (r < m_depthSegments){
				wireframe->Push(index, index + widthCount);
			}

			currentX += stepX;
		}
	}

	shaded->Push(baseIndex, baseIndex + m_widthSegments, baseIndex + m_depthSegments * widthCount);
	shaded->Push(baseIndex + m_widthSegments, baseIndex + m_depthSegments * widthCount, geometry.VertexCount() - 1);
}

void rPrimitiveBox::GenerateLeftRight(rGeometryData& geometry, float x, const rVector3& normal){
	float stepY = m_height / (float)m_heightSegments;
	float stepZ = m_depth / (float)m_depthSegments;

	rVector3 vertex;
	rVector2 texCoord = rVector2::ZeroVector;

	rElementBufferData* wireframe = geometry.GetElementBuffer("wire");
	rElementBufferData* shaded = geometry.GetElementBuffer("shaded");

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

			vertex.Set(x, currentY, currentZ);
			geometry.PushVertex(vertex, normal, texCoord);

			if (c < m_depthSegments){
				wireframe->Push(index, index + 1);
			}

			if (r < m_heightSegments){
				wireframe->Push(index, index + depthCount);
			}

			currentZ += stepZ;
		}
	}

	shaded->Push(baseIndex, baseIndex + m_depthSegments, baseIndex + m_heightSegments * depthCount);
	shaded->Push(baseIndex + m_depthSegments, baseIndex + m_heightSegments * depthCount, geometry.VertexCount() - 1);
}

void rPrimitiveBox::CreateGeometry(rGeometryData& geometry){
	geometry.CreateElementBuffer("wire", rGEOMETRY_LINES);
	geometry.CreateElementBuffer("shaded", rGEOMETRY_TRIANGLES);

	float halfWidth = m_width / 2.0f;
	float halfDepth = m_depth / 2.0f;

	
	GenerateFrontBack(geometry, m_position.z - halfDepth, rVector3::BackwardVector);	//generate back
	GenerateFrontBack(geometry, m_position.z + halfDepth, rVector3::ForwardVector);	//generate front

	GenerateTopBottom(geometry, m_position.y, rVector3::DownVector);				//generate bottom
	GenerateTopBottom(geometry, m_position.y + m_height, rVector3::UpVector);		//generate top

	GenerateLeftRight(geometry, m_position.x - halfWidth, rVector3::LeftVector);	//generate left
	GenerateLeftRight(geometry, m_position.x + halfWidth, rVector3::RightVector);	//generate right
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