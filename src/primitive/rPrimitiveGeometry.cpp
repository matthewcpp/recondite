#include "primitive/rPrimitiveGeometry.hpp"

//common

void EnsureBuffers(const rPrimitiveGeometry::rPrimitiveParams& params, rGeometryData& geometryData){
	if (!geometryData.GetElementBuffer(params.faceMeshName)){
		geometryData.CreateElementBuffer(params.faceMeshName, rGeometryType::TRIANGLES);
	}

	if (!geometryData.GetElementBuffer(params.wireMeshName)){
		geometryData.CreateElementBuffer(params.wireMeshName, rGeometryType::LINES);
	}
}

//Primitive Box
void GenerateBoxFrontBack(rGeometryData& geometry, const rPrimitiveGeometry::rPrimitiveBoxParams& params, float z, const rVector3& normal){
	float stepX = params.extents.x / (float)params.widthSegments;
	float stepY = params.extents.y / (float)params.heightSegments;

	rVector3 vertex;

	rElementBufferData* wireframe = geometry.GetElementBuffer(params.wireMeshName);
	rElementBufferData* shaded = geometry.GetElementBuffer(params.faceMeshName);

	float halfWidth = params.extents.x / 2.0f;
	float halfDepth = params.extents.y / 2.0f;

	float startX, startY;
	int widthCount = params.widthSegments + 1;
	int heightCount = params.heightSegments + 1;
	size_t baseIndex = geometry.VertexCount();
	startX = -halfWidth;
	startY = 0.0f;

	for (int r = 0; r < heightCount; r++){
		float currentX = startX;
		float currentY = startY + params.extents.y - ((float)r * stepY);

		for (int c = 0; c < widthCount; c++){
			int index = baseIndex + (r * widthCount) + c;

			vertex.Set(currentX, currentY, z);
			geometry.PushVertex(vertex, normal);

			if (c < params.widthSegments){
				wireframe->Push(index, index + 1);
			}

			if (r < params.heightSegments){
				wireframe->Push(index, index + widthCount);
			}

			currentX += stepX;
		}
	}

	shaded->Push(baseIndex, baseIndex + params.widthSegments, baseIndex + params.heightSegments * widthCount);
	shaded->Push(baseIndex + params.widthSegments, baseIndex + params.heightSegments * widthCount, geometry.VertexCount() - 1);
}

void GenerateBoxTopBottom(rGeometryData& geometry, const rPrimitiveGeometry::rPrimitiveBoxParams& params, float y, const rVector3& normal){
	float stepX = params.extents.x / (float)params.widthSegments;
	float stepZ = params.extents.z / (float)params.depthSegments;

	rVector3 vertex;

	rElementBufferData* wireframe = geometry.GetElementBuffer(params.wireMeshName);
	rElementBufferData* shaded = geometry.GetElementBuffer(params.faceMeshName);

	float halfWidth = params.extents.x / 2.0f;
	float halfDepth = params.extents.z / 2.0f;

	float startX, startZ;
	int widthCount = params.widthSegments + 1;
	int depthCount = params.depthSegments + 1;
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

			if (c < params.widthSegments){
				wireframe->Push(index, index + 1);
			}

			if (r < params.depthSegments){
				wireframe->Push(index, index + widthCount);
			}

			currentX += stepX;
		}
	}

	shaded->Push(baseIndex, baseIndex + params.widthSegments, baseIndex + params.depthSegments * widthCount);
	shaded->Push(baseIndex + params.widthSegments, baseIndex + params.depthSegments * widthCount, geometry.VertexCount() - 1);
}

void GenerateBoxLeftRight(rGeometryData& geometry, const rPrimitiveGeometry::rPrimitiveBoxParams& params, float x, const rVector3& normal){
	float stepY = params.extents.y / (float)params.heightSegments;
	float stepZ = params.extents.z / (float)params.depthSegments;

	rVector3 vertex;

	rElementBufferData* wireframe = geometry.GetElementBuffer(params.wireMeshName);
	rElementBufferData* shaded = geometry.GetElementBuffer(params.faceMeshName);

	float halfDepth = params.extents.z / 2.0f;

	float startY, startZ;
	int depthCount = params.depthSegments + 1;
	int heightCount = params.heightSegments + 1;
	size_t baseIndex = geometry.VertexCount();
	startY = params.extents.y;
	startZ = -halfDepth;

	for (int r = 0; r < heightCount; r++){
		float currentZ = startZ;
		float currentY = startY - ((float)r * stepY);

		for (int c = 0; c < depthCount; c++){
			int index = baseIndex + (r * depthCount) + c;

			vertex.Set(x, currentY, currentZ);
			geometry.PushVertex(vertex, normal);

			if (c < params.depthSegments){
				wireframe->Push(index, index + 1);
			}

			if (r < params.heightSegments){
				wireframe->Push(index, index + depthCount);
			}

			currentZ += stepZ;
		}
	}

	shaded->Push(baseIndex, baseIndex + params.depthSegments, baseIndex + params.heightSegments * depthCount);
	shaded->Push(baseIndex + params.depthSegments, baseIndex + params.heightSegments * depthCount, geometry.VertexCount() - 1);
}

void rPrimitiveGeometry::CreateBox(const rPrimitiveBoxParams& params, rGeometryData& geometry){
	EnsureBuffers(params, geometry);

	float halfWidth = params.extents.x / 2.0f;
	float halfDepth = params.extents.z / 2.0f;

	GenerateBoxFrontBack(geometry, params, -halfDepth, rVector3::BackwardVector);	//generate back
	GenerateBoxFrontBack(geometry, params, halfDepth, rVector3::ForwardVector);	//generate front

	GenerateBoxTopBottom(geometry, params, 0.0f, rVector3::DownVector);				//generate bottom
	GenerateBoxTopBottom(geometry, params, params.extents.y, rVector3::UpVector);		//generate top

	GenerateBoxLeftRight(geometry, params, -halfWidth, rVector3::LeftVector);	//generate left
	GenerateBoxLeftRight(geometry, params, halfWidth, rVector3::RightVector);	//generate right
}

//Primitive Grid
void rPrimitiveGeometry::CreateGrid(const rPrimitiveGeometry::rPrimitiveGridParams& params, rGeometryData& geometry){
	EnsureBuffers(params, geometry);

	rElementBufferData* wireframe = geometry.GetElementBuffer(params.wireMeshName);
	rElementBufferData* shaded = geometry.GetElementBuffer(params.faceMeshName);

	float stepX = params.width / (float)params.columns;
	float stepZ = params.depth / (float)params.rows;

	rVector3 vertex;
	rVector3 normal = rVector3::UpVector;

	float halfWidth = params.width / 2.0f;
	float halfDepth = params.depth / 2.0f;

	float startX, startZ;
	int widthCount = params.columns + 1;
	int depthCount = params.rows + 1;
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

			if (c < params.columns)
				wireframe->Push(index, index + 1);

			if (r < params.rows)
				wireframe->Push(index, index + widthCount);

			currentX += stepX;
		}
	}

	shaded->Push(0, params.columns, params.rows * widthCount);
	shaded->Push(params.columns, params.rows * widthCount, geometry.VertexCount() - 1);
}

//Circle

void rPrimitiveGeometry::CreateCircle(const rPrimitiveGeometry::rPrimitiveCircleParams& params, rGeometryData& geometry){
	EnsureBuffers(params, geometry);

	rElementBufferData* wireframe = geometry.GetElementBuffer(params.wireMeshName);
	rElementBufferData* shaded = geometry.GetElementBuffer(params.faceMeshName);

	float step = 360.0f / (float)params.segmentCount;

	rVector3 position;

	size_t baseIndex = geometry.VertexCount();
	geometry.PushVertex(params.center, params.normal);

	for (size_t i = 0; i < params.segmentCount; i++){
		float angle = float(i) * step;
		float radians = rMath::DegreeToRad(angle);

		position.Set(std::cos(radians), 0.0f, std::sin(radians));
		position += params.center;
		position *= params.radius;

		geometry.PushVertex(position, params.normal);

		if (i > 0){
			wireframe->Push(baseIndex + i, baseIndex + i + 1);
			shaded->Push(baseIndex, baseIndex + i, baseIndex + i + 1);
		}
	}

	wireframe->Push(baseIndex + params.segmentCount, baseIndex + 1);
	shaded->Push(baseIndex, baseIndex + params.segmentCount, baseIndex + 1);
}

//Cone

void CreateConeFace(rGeometryData& geometry, size_t v1, size_t v2, const rPrimitiveGeometry::rPrimitiveConeParams& params, float coneAngle){
	rElementBufferData* wireframe = geometry.GetElementBuffer(params.wireMeshName);
	rElementBufferData* shaded = geometry.GetElementBuffer(params.faceMeshName);

	rVector3 tip = rVector3::UpVector * params.height;
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

void rPrimitiveGeometry::CreateCone(const rPrimitiveGeometry::rPrimitiveConeParams& params, rGeometryData& geometry){
	EnsureBuffers(params, geometry);
	rElementBufferData* wireframe = geometry.GetElementBuffer(params.wireMeshName);
	rElementBufferData* shaded = geometry.GetElementBuffer(params.faceMeshName);

	size_t baseIndex = geometry.VertexCount();

	rPrimitiveCircleParams circleParams(rVector3::ZeroVector, rVector3::DownVector, params.radius, params.segmentCount);
	CreateCircle(circleParams, geometry);

	float coneAngle = std::atan(params.radius / params.height);

	for (size_t i = 0; i < params.segmentCount; i++){
		CreateConeFace(geometry, baseIndex + i + 1, baseIndex + i + 2, params, coneAngle);
	}

	CreateConeFace(geometry, baseIndex + params.segmentCount, baseIndex + 1, params, coneAngle);
}

//Cylinder
void CreateCylinderFace(const rPrimitiveGeometry::rPrimitiveCylinderParams& params, rGeometryData& geometry, int i1, int i2, int i3, int i4){
	rElementBufferData* shaded = geometry.GetElementBuffer(params.faceMeshName);

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


void rPrimitiveGeometry::CreateCylinder(const rPrimitiveGeometry::rPrimitiveCylinderParams& params, rGeometryData& geometry){
	EnsureBuffers(params, geometry);

	rElementBufferData* wireframe = geometry.GetElementBuffer(params.wireMeshName);
	rElementBufferData* shaded = geometry.GetElementBuffer(params.faceMeshName);

	rPrimitiveCircleParams circleParams(rVector3::ZeroVector, rVector3::DownVector, params.radius, params.segmentCount);
	circleParams.faceMeshName = params.faceMeshName;
	circleParams.wireMeshName = params.wireMeshName;

	CreateCircle(circleParams, geometry);

	circleParams.center = rVector3::UpVector;
	circleParams.normal = rVector3::UpVector;

	CreateCircle(circleParams, geometry);

	for (int i = 1; i <= params.segmentCount; i++){
		wireframe->Push(i, i + params.segmentCount + 1);

		if (i > 1) CreateCylinderFace(params, geometry, i - 1, i, i + params.segmentCount, i + params.segmentCount + 1);
	}

	CreateCylinderFace(params, geometry, params.segmentCount, 2 * params.segmentCount + 1, 1, params.segmentCount + 2);
}

//Sphere

void rPrimitiveGeometry::CreateSphere(const rPrimitiveSphereParams& params, rGeometryData& geometry){
	EnsureBuffers(params, geometry);
	rElementBufferData* wireframe = geometry.GetElementBuffer(params.wireMeshName);
	rElementBufferData* shaded = geometry.GetElementBuffer(params.faceMeshName);

	rVector3 center(0, params.radius, 0);
	rVector3 position = rVector3::ZeroVector;
	rVector3 normal = rVector3::ZeroVector;

	float R = 1.0f / (float)(params.rings - 1);
	float S = 1.0f / (float)(params.sectors - 1);
	int r, s;

	for (r = 0; r < params.rings; r++){
		for (s = 0; s < params.sectors; s++) {
			float y = std::sin(-M_PI_2 + M_PI * r * R);
			float x = std::cos(2 * M_PI * s * S) * std::sin(M_PI * r * R);
			float z = std::sin(2 * M_PI * s * S) * std::sin(M_PI * r * R);

			position.Set(x, y + params.radius, z);
			normal = position - center;
			normal.Normalize();
			position *= params.radius;

			geometry.PushVertex(position, normal);
		}
	}

	//generate indicies
	for (r = 0; r < params.rings - 1; r++) {
		for (s = 0; s < params.sectors - 1; s++) {
			int p1 = r * params.sectors + s;
			int p2 = r * params.sectors + (s + 1);
			int p3 = (r + 1) * params.sectors + (s + 1);
			int p4 = (r + 1) * params.sectors + s;

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