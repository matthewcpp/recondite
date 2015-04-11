#include "primitive/rPrimitiveGeometry.hpp"

//common
void EnsureBuffers(rGeometryData& geometry){
	if (!geometry.GetElementBuffer("wire"))
		geometry.CreateElementBuffer("wire", rGeometryType::LINES);

	if (!geometry.GetElementBuffer("shaded"))
		geometry.CreateElementBuffer("shaded", rGeometryType::TRIANGLES);
}

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
	EnsureBuffers(geometry);

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

	rElementBufferData* wireframe = geometry.CreateElementBuffer("wire", rGeometryType::LINES);
	rElementBufferData* shaded = geometry.CreateElementBuffer("shaded", rGeometryType::TRIANGLES);

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

//Circle

void rPrimitiveGeometry::CreateCircle(const rVector3& center, float radius, const rVector3& normal, size_t segmentCount, rGeometryData& geometry){
	EnsureBuffers(geometry);

	rElementBufferData* wireframe = geometry.GetElementBuffer("wire");
	rElementBufferData* shaded = geometry.GetElementBuffer("shaded");

	float step = 360.0f / (float)segmentCount;

	rVector3 position;

	size_t baseIndex = geometry.VertexCount();
	geometry.PushVertex(center, normal);

	for (size_t i = 0; i < segmentCount; i++){
		float angle = float(i) * step;
		float radians = rMath::DegreeToRad(angle);

		position.Set(std::cos(radians), 0.0f, std::sin(radians));
		position *= radius;
		position += center;

		geometry.PushVertex(position, normal);

		if (i > 0){
			wireframe->Push(baseIndex + i, baseIndex + i + 1);
			shaded->Push(baseIndex, baseIndex + i, baseIndex + i + 1);
		}
	}

	wireframe->Push(baseIndex + segmentCount, baseIndex + 1);
	shaded->Push(baseIndex, baseIndex + segmentCount, baseIndex + 1);
}

//Cone

void CreateConeFace(rGeometryData& geometry, size_t v1, size_t v2, float height, float coneAngle){
	rElementBufferData* wireframe = geometry.GetElementBuffer("wire");
	rElementBufferData* shaded = geometry.GetElementBuffer("shaded");

	rVector3 tip = rVector3::UpVector * height;
	rVector3 p1, p2, n1, n2;

	geometry.GetVertex(v1, &p1, nullptr);
	n1 = p1.GetNormalized();
	n1 *= std::cos(coneAngle);
	n1.y = std::sin(coneAngle);

	geometry.GetVertex(v2, &p2, nullptr);
	n2 = p1.GetNormalized();
	n2 *= std::cos(coneAngle);
	n2.y = std::sin(coneAngle);

	size_t baseIndex = geometry.VertexCount();
	geometry.PushVertex(tip, n1);
	geometry.PushVertex(p1, n1);
	geometry.PushVertex(p2, n2);
	shaded->Push(baseIndex, baseIndex + 1, baseIndex + 2);

	wireframe->Push(baseIndex, baseIndex + 1);
	wireframe->Push(baseIndex, baseIndex + 2);
}

void rPrimitiveGeometry::CreateCone(float radius, float height, size_t segmentCount, rGeometryData& geometry){
	EnsureBuffers(geometry);
	rElementBufferData* wireframe = geometry.GetElementBuffer("wire");
	rElementBufferData* shaded = geometry.GetElementBuffer("shaded");

	size_t baseIndex = geometry.VertexCount();

	CreateCircle(rVector3::ZeroVector, radius, rVector3::DownVector, segmentCount, geometry);

	float coneAngle = std::atan(radius / height);

	for (size_t i = 0; i < segmentCount; i++){
		CreateConeFace(geometry, baseIndex + i + 1, baseIndex + i + 2, height, coneAngle);
	}

	CreateConeFace(geometry, baseIndex + segmentCount, baseIndex + 1, height, coneAngle);
}

//Cylinder
void CreateCylinderFace(rGeometryData& geometry, int i1, int i2, int i3, int i4){
	rElementBufferData* shaded = geometry.GetElementBuffer("shaded");

	rVector3 v1, v2, v3, v4, n1, n2, n3, n4;
	size_t baseIndex = geometry.VertexCount();

	geometry.GetVertex(i1, &v1, nullptr);
	n1 = v1;

	geometry.GetVertex(i2, &v2, nullptr);
	n2 = v2;

	geometry.GetVertex(i3, &v3, nullptr);
	n3 = v3;

	geometry.GetVertex(i4, &v4, nullptr);
	n4 = v4;

	geometry.PushVertex(v1, n1);
	geometry.PushVertex(v2, n2);
	geometry.PushVertex(v3, n3);
	geometry.PushVertex(v4, n4);

	shaded->Push(baseIndex, baseIndex + 2, baseIndex + 3);
	shaded->Push(baseIndex, baseIndex + 1, baseIndex + 3);
}


void rPrimitiveGeometry::CreateCylinder(float radius, float height, size_t segmentCount, rGeometryData& geometry){
	EnsureBuffers(geometry);

	rElementBufferData* wireframe = geometry.GetElementBuffer("wire");
	rElementBufferData* shaded = geometry.GetElementBuffer("shaded");

	CreateCircle(rVector3::ZeroVector, radius, rVector3::DownVector, segmentCount, geometry);
	CreateCircle(rVector3::UpVector * height, radius, rVector3::UpVector, segmentCount, geometry);

	for (int i = 1; i <= segmentCount; i++){
		wireframe->Push(i, i + segmentCount + 1);

		if (i > 1) CreateCylinderFace(geometry, i - 1, i, i + segmentCount, i + segmentCount + 1);
	}

	CreateCylinderFace(geometry, segmentCount, 2 * segmentCount + 1, 1, segmentCount + 2);
}

//Sphere

void rPrimitiveGeometry::CreateSphere(float radius, size_t rings, size_t sectors, rGeometryData& geometry){
	EnsureBuffers(geometry);

	rElementBufferData* wireframe = geometry.GetElementBuffer("wire");
	rElementBufferData* shaded = geometry.GetElementBuffer("shaded");

	rVector3 center(0, radius, 0);
	rVector3 position = rVector3::ZeroVector;
	rVector3 normal = rVector3::ZeroVector;

	float R = 1.0f / (float)(rings - 1);
	float S = 1.0f / (float)(sectors - 1);
	int r, s;

	for (r = 0; r < rings; r++){
		for (s = 0; s < sectors; s++) {
			float y = std::sin(-M_PI_2 + M_PI * r * R);
			float x = std::cos(2 * M_PI * s * S) * std::sin(M_PI * r * R);
			float z = std::sin(2 * M_PI * s * S) * std::sin(M_PI * r * R);

			position.Set(x, y + radius, z);
			normal = position - center;
			normal.Normalize();
			position *= radius;

			geometry.PushVertex(position, normal);
		}
	}

	//generate indicies
	for (r = 0; r < rings - 1; r++) {
		for (s = 0; s < sectors - 1; s++) {
			int p1 = r * sectors + s;
			int p2 = r * sectors + (s + 1);
			int p3 = (r + 1) * sectors + (s + 1);
			int p4 = (r + 1) * sectors + s;

			//lines
			wireframe->Push(p1, p2);
			wireframe->Push(p2, p3);
			wireframe->Push(p3, p4);
			wireframe->Push(p4, p1);

			//faces
			shaded->Push(p1, p2, p4);
			shaded->Push(p2, p4, p3);
		}
	}
}