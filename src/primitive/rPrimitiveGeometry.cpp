#include "primitive/rPrimitiveGeometry.hpp"

//Primitive Box

void GenerateBoxFrontBack(rGeometryData& geometry, const rVector3& extents, std::tuple<int, int, int> segmentCounts, float z, const rVector3& normal){
	int widthSegments = std::get<0>(segmentCounts);
	int heightSegments = std::get<1>(segmentCounts);

	float stepX = extents.x / (float)widthSegments;
	float stepY = extents.y / (float)heightSegments;

	rVector3 vertex;

	rElementBufferData* wireframe = geometry.GetElementBuffer("wire");
	rElementBufferData* shaded = geometry.GetElementBuffer("shaded");

	float halfWidth = extents.x / 2.0f;
	float halfDepth = extents.y / 2.0f;

	float startX, startY;
	int widthCount = widthSegments + 1;
	int heightCount = heightSegments + 1;
	size_t baseIndex = geometry.VertexCount();
	startX = -halfWidth;
	startY = 0.0f;

	for (int r = 0; r < heightCount; r++){
		float currentX = startX;
		float currentY = startY + extents.y - ((float)r * stepY);

		for (int c = 0; c < widthCount; c++){
			int index = baseIndex + (r * widthCount) + c;

			vertex.Set(currentX, currentY, z);
			geometry.PushVertex(vertex, normal);

			if (c < widthSegments){
				wireframe->Push(index, index + 1);
			}

			if (r < heightSegments){
				wireframe->Push(index, index + widthCount);
			}

			currentX += stepX;
		}
	}

	shaded->Push(baseIndex, baseIndex + widthSegments, baseIndex + heightSegments * widthCount);
	shaded->Push(baseIndex + widthSegments, baseIndex + heightSegments * widthCount, geometry.VertexCount() - 1);
}

void GenerateBoxTopBottom(rGeometryData& geometry, const rVector3& extents, std::tuple<int, int, int> segmentCounts, float y, const rVector3& normal){
	int widthSegments = std::get<0>(segmentCounts);
	int depthSegments = std::get<2>(segmentCounts);

	float stepX = extents.x / (float)widthSegments;
	float stepZ = extents.z / (float)depthSegments;

	rVector3 vertex;

	rElementBufferData* wireframe = geometry.GetElementBuffer("wire");
	rElementBufferData* shaded = geometry.GetElementBuffer("shaded");

	float halfWidth = extents.x / 2.0f;
	float halfDepth = extents.z / 2.0f;

	float startX, startZ;
	int widthCount = widthSegments + 1;
	int depthCount = depthSegments + 1;
	size_t baseIndex = geometry.VertexCount();
	startX = -halfWidth;
	startZ = -halfDepth;

	for (int r = 0; r < depthCount; r++){
		float currentX = startX;
		float currentZ = startZ + ((float)r * stepZ);

		for (int c = 0; c < widthCount; c++){
			int index = baseIndex + (r * widthCount) + c;

			vertex.Set(currentX, y, currentZ);
			geometry.PushVertex(vertex, normal);

			if (c < widthSegments){
				wireframe->Push(index, index + 1);
			}

			if (r < depthSegments){
				wireframe->Push(index, index + widthCount);
			}

			currentX += stepX;
		}
	}

	shaded->Push(baseIndex, baseIndex + widthSegments, baseIndex + depthSegments * widthCount);
	shaded->Push(baseIndex + widthSegments, baseIndex + depthSegments * widthCount, geometry.VertexCount() - 1);
}

void GenerateBoxLeftRight(rGeometryData& geometry, const rVector3& extents, std::tuple<int, int, int> segmentCounts, float x, const rVector3& normal){
	int heightSegments = std::get<1>(segmentCounts);
	int depthSegments = std::get<2>(segmentCounts);

	float stepY = extents.y / (float)heightSegments;
	float stepZ = extents.z / (float)depthSegments;

	rVector3 vertex;

	rElementBufferData* wireframe = geometry.GetElementBuffer("wire");
	rElementBufferData* shaded = geometry.GetElementBuffer("shaded");

	float halfDepth = extents.z / 2.0f;

	float startY, startZ;
	int depthCount = depthSegments + 1;
	int heightCount = heightSegments + 1;
	size_t baseIndex = geometry.VertexCount();
	startY = extents.y;
	startZ = -halfDepth;

	for (int r = 0; r < heightCount; r++){
		float currentZ = startZ;
		float currentY = startY - ((float)r * stepY);

		for (int c = 0; c < depthCount; c++){
			int index = baseIndex + (r * depthCount) + c;

			vertex.Set(x, currentY, currentZ);
			geometry.PushVertex(vertex, normal);

			if (c < depthSegments){
				wireframe->Push(index, index + 1);
			}

			if (r < heightSegments){
				wireframe->Push(index, index + depthCount);
			}

			currentZ += stepZ;
		}
	}

	shaded->Push(baseIndex, baseIndex + depthSegments, baseIndex + heightSegments * depthCount);
	shaded->Push(baseIndex + depthSegments, baseIndex + heightSegments * depthCount, geometry.VertexCount() - 1);
}

void rPrimitiveGeometry::CreateBox(const rVector3& extents, std::tuple<int, int, int> segmentCounts, rGeometryData& geometry){
	geometry.CreateElementBuffer("wire", rGEOMETRY_LINES);
	geometry.CreateElementBuffer("shaded", rGEOMETRY_TRIANGLES);

	float halfWidth = extents.x / 2.0f;
	float halfDepth = extents.z / 2.0f;

	GenerateBoxFrontBack(geometry, extents, segmentCounts, -halfDepth, rVector3::BackwardVector);	//generate back
	GenerateBoxFrontBack(geometry, extents, segmentCounts, halfDepth, rVector3::ForwardVector);	//generate front

	GenerateBoxTopBottom(geometry, extents, segmentCounts, 0.0f, rVector3::DownVector);				//generate bottom
	GenerateBoxTopBottom(geometry, extents, segmentCounts, extents.y, rVector3::UpVector);		//generate top

	GenerateBoxLeftRight(geometry, extents, segmentCounts,-halfWidth, rVector3::LeftVector);	//generate left
	GenerateBoxLeftRight(geometry, extents, segmentCounts,halfWidth, rVector3::RightVector);	//generate right
}

//Primitive Grid
void rPrimitiveGeometry::CreateGrid(const rVector3& extents, std::tuple<int, int> segmentCounts, rGeometryData& geometry){
	int columns = std::get<0>(segmentCounts);
	int rows = std::get<1>(segmentCounts);

	rElementBufferData* wireframe = geometry.CreateElementBuffer("wire", rGEOMETRY_LINES);
	rElementBufferData* shaded = geometry.CreateElementBuffer("shaded", rGEOMETRY_TRIANGLES);

	float stepX = extents.x / (float)columns;
	float stepZ = extents.z / (float)rows;

	rVector3 vertex;
	rVector3 normal = rVector3::UpVector;

	float halfWidth = extents.x / 2.0f;
	float halfDepth = extents.z / 2.0f;

	float startX, startZ;
	int widthCount = columns + 1;
	int depthCount = rows + 1;
	size_t baseIndex = geometry.VertexCount();
	startX = -halfWidth;
	startZ = -halfDepth;

	for (int r = 0; r < depthCount; r++){
		float currentX = startX;
		float currentZ = startZ + ((float)r * stepZ);

		for (int c = 0; c < widthCount; c++){
			int index = baseIndex + (r * widthCount) + c;

			vertex.Set(currentX, 0.0f, currentZ);
			geometry.PushVertex(vertex, normal);

			if (c < columns)
				wireframe->Push(index, index + 1);

			if (r < rows)
				wireframe->Push(index, index + widthCount);

			currentX += stepX;
		}
	}

	shaded->Push(0, columns, rows * widthCount);
	shaded->Push(columns, rows * widthCount, geometry.VertexCount() - 1);
}