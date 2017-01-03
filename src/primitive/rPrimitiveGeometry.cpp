#include "primitive/rPrimitiveGeometry.hpp"

//common

void EnsureBuffers(const rPrimitiveGeometry::rPrimitiveParams& params, ModelData& modelData){
	if (params.createFaceMesh && modelData.GetTriangleMeshCount() == 0) {
		MeshData* mesh = modelData.CreateTriangleMesh();
		mesh->SetName(params.faceMeshName);
	}

	if (params.createWireMesh && modelData.GetLineMeshCount() == 0) {
		MeshData* mesh = modelData.CreateLineMesh();
		mesh->SetName(params.wireMeshName);
	}
}

//Primitive Box
void GenerateBoxFrontBack(ModelData& modelData, const rPrimitiveGeometry::rPrimitiveBoxParams& params, float z, const rVector3& normal){
	GeometryData& geometry = *modelData.GetGeometryData();
	MeshData* shaded = modelData.GetTriangleMesh(modelData.GetTriangleMeshCount() - 1);
	MeshData* wireframe = modelData.GetLineMesh(modelData.GetLineMeshCount() - 1);

	float stepX = params.extents.x / (float)params.widthSegments;
	float stepY = params.extents.y / (float)params.heightSegments;

	rVector3 vertex;

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
			geometry.PushVertex(vertex);
			geometry.PushNormal(normal);

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

void GenerateBoxTopBottom(ModelData& modelData, const rPrimitiveGeometry::rPrimitiveBoxParams& params, float y, const rVector3& normal){
	GeometryData& geometry = *modelData.GetGeometryData();
	MeshData* shaded = modelData.GetTriangleMesh(modelData.GetTriangleMeshCount() - 1);
	MeshData* wireframe = modelData.GetLineMesh(modelData.GetLineMeshCount() - 1);

	float stepX = params.extents.x / (float)params.widthSegments;
	float stepZ = params.extents.z / (float)params.depthSegments;

	rVector3 vertex;

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
			geometry.PushVertex(vertex);
			geometry.PushNormal(normal);

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

void GenerateBoxLeftRight(ModelData& modelData, const rPrimitiveGeometry::rPrimitiveBoxParams& params, float x, const rVector3& normal){
	GeometryData& geometry = *modelData.GetGeometryData();
	MeshData* shaded = modelData.GetTriangleMesh(modelData.GetTriangleMeshCount() - 1);
	MeshData* wireframe = modelData.GetLineMesh(modelData.GetLineMeshCount() - 1);

	float stepY = params.extents.y / (float)params.heightSegments;
	float stepZ = params.extents.z / (float)params.depthSegments;

	rVector3 vertex;

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
			geometry.PushVertex(vertex);
			geometry.PushNormal(normal);

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

void rPrimitiveGeometry::CreateBox(const rPrimitiveBoxParams& params, ModelData& modelData){
	EnsureBuffers(params, modelData);

	float halfWidth = params.extents.x / 2.0f;
	float halfDepth = params.extents.z / 2.0f;

	GenerateBoxFrontBack(modelData, params, -halfDepth, rVector3::ForwardVector);	//generate back
	GenerateBoxFrontBack(modelData, params, halfDepth, rVector3::BackwardVector);	//generate front

	GenerateBoxTopBottom(modelData, params, 0.0f, rVector3::DownVector);				//generate bottom
	GenerateBoxTopBottom(modelData, params, params.extents.y, rVector3::UpVector);		//generate top

	GenerateBoxLeftRight(modelData, params, -halfWidth, rVector3::LeftVector);	//generate left
	GenerateBoxLeftRight(modelData, params, halfWidth, rVector3::RightVector);	//generate right
}

//Primitive Grid
void rPrimitiveGeometry::CreateGrid(const rPrimitiveGeometry::rPrimitiveGridParams& params, ModelData& modelData){
	EnsureBuffers(params, modelData);

	GeometryData& geometry = *modelData.GetGeometryData();
	MeshData* shaded = modelData.GetTriangleMesh(modelData.GetTriangleMeshCount() - 1);
	MeshData* wireframe = modelData.GetLineMesh(modelData.GetLineMeshCount() - 1);

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
			geometry.PushVertex(vertex);
			geometry.PushNormal(normal);

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

void rPrimitiveGeometry::CreateCircle(const rPrimitiveGeometry::rPrimitiveCircleParams& params, ModelData& modelData){
	EnsureBuffers(params, modelData);

	GeometryData& geometry = *modelData.GetGeometryData();
	MeshData* shaded = modelData.GetTriangleMesh(modelData.GetTriangleMeshCount() - 1);
	MeshData* wireframe = modelData.GetLineMesh(modelData.GetLineMeshCount() - 1);

	float step = (params.end - params.start) / (float)params.segmentCount;

	rVector3 position;

	size_t baseIndex = geometry.VertexCount();
	geometry.PushVertex(params.center);
	geometry.PushNormal(params.normal);

	for (size_t i = 0; i <= params.segmentCount; i++){
		float angle = params.start + (float(i) * step);
		float radians = rMath::DegreeToRad(angle);

		position.Set(std::cos(radians), 0.0f, std::sin(radians));
		position *= params.radius;
		position += params.center;
		
		geometry.PushVertex(position);
		geometry.PushNormal(params.normal);

		if (i > 0){
			wireframe->Push(baseIndex + i, baseIndex + i + 1);
			shaded->Push(baseIndex, baseIndex + i, baseIndex + i + 1);
		}
	}
}

//Cone

void CreateConeFace(ModelData& modelData, size_t v1, size_t v2, const rPrimitiveGeometry::rPrimitiveConeParams& params, float coneAngle){
	GeometryData& geometry = *modelData.GetGeometryData();
	MeshData* shaded = modelData.GetTriangleMesh(modelData.GetTriangleMeshCount() - 1);
	MeshData* wireframe = modelData.GetLineMesh(modelData.GetLineMeshCount() - 1);

	rVector3 tip = rVector3::UpVector * params.height;
	rVector3 p1, p2, n1, n2;

	geometry.GetVertex(v1, p1);
	n1 = p1.GetNormalized();
	n1 *= std::cos(coneAngle);
	n1.y = std::sin(coneAngle);

	geometry.GetVertex(v2, p2);
	n2 = p1.GetNormalized();
	n2 *= std::cos(coneAngle);
	n2.y = std::sin(coneAngle);

	size_t baseIndex = geometry.VertexCount();
	geometry.PushVertex(tip);
	geometry.PushNormal(n1);

	geometry.PushVertex(p1);
	geometry.PushNormal(n1);

	geometry.PushVertex(p2);
	geometry.PushNormal(n2);

	shaded->Push(baseIndex, baseIndex + 1, baseIndex + 2);

	wireframe->Push(baseIndex, baseIndex + 1);
	wireframe->Push(baseIndex, baseIndex + 2);
}

void rPrimitiveGeometry::CreateCone(const rPrimitiveGeometry::rPrimitiveConeParams& params, ModelData& modelData){
	EnsureBuffers(params, modelData);

	size_t baseIndex = modelData.GetGeometryData()->VertexCount();

	rPrimitiveCircleParams circleParams(rVector3::ZeroVector, rVector3::DownVector, params.radius, params.segmentCount);
	CreateCircle(circleParams, modelData);

	float coneAngle = std::atan(params.radius / params.height);

	for (size_t i = 0; i < params.segmentCount; i++){
		CreateConeFace(modelData, baseIndex + i + 1, baseIndex + i + 2, params, coneAngle);
	}

	CreateConeFace(modelData, baseIndex + params.segmentCount, baseIndex + 1, params, coneAngle);
}

void rPrimitiveGeometry::CreateCylinder(const rPrimitiveGeometry::rPrimitiveCylinderParams& params, ModelData& modelData){
	EnsureBuffers(params, modelData);

	rPrimitiveCircleParams circleParams(rVector3::ZeroVector, rVector3::DownVector, params.radius, params.segmentCount);
	circleParams.faceMeshName = params.faceMeshName;
	circleParams.wireMeshName = params.wireMeshName;

	recondite::GeometryData* geometryData = modelData.GetGeometryData();
	size_t bottomIndex = geometryData->VertexCount() + 1;
	CreateCircle(circleParams, modelData);

	circleParams.center = rVector3::UpVector * params.height;
	circleParams.normal = rVector3::UpVector;

	size_t topIndex = geometryData->VertexCount() + 1;
	CreateCircle(circleParams, modelData);

	MeshData* shaded = modelData.GetTriangleMesh(modelData.GetTriangleMeshCount() - 1);
	MeshData* wireframe = modelData.GetLineMesh(modelData.GetLineMeshCount() - 1);

	size_t baseIndex = geometryData->VertexCount();

	rVector3 v1, v2, n;
	float step = 360.0f / (float)params.segmentCount;
	for (size_t i = 0; i <= params.segmentCount; i++) {
		float angle = float(i) * step;
		float radians = rMath::DegreeToRad(angle);
		uint16_t ref = (i * 2) + baseIndex;

		n.Set(std::cos(radians), 0.0f, std::sin(radians));
		geometryData->GetVertex(bottomIndex + i, v1);
		geometryData->GetVertex(topIndex + i, v2);
		
		geometryData->PushVertex(v1);
		geometryData->PushNormal(n);

		geometryData->PushVertex(v2);
		geometryData->PushNormal(n);

		wireframe->Push(ref, ref + 1);

		if (i > 0) {
			shaded->Push(ref - 2, ref, ref + 1);
			shaded->Push(ref - 2, ref + 1, ref - 1);
		}
	}
}

//Sphere

void rPrimitiveGeometry::CreateSphere(const rPrimitiveSphereParams& params, ModelData& modelData){
	EnsureBuffers(params, modelData);

	GeometryData& geometry = *modelData.GetGeometryData();
	MeshData* shaded = modelData.GetTriangleMesh(modelData.GetTriangleMeshCount() - 1);
	MeshData* wireframe = modelData.GetLineMesh(modelData.GetLineMeshCount() - 1);

	rVector3 center(0, params.radius, 0);
	rVector3 position = rVector3::ZeroVector;
	rVector3 normal = rVector3::ZeroVector;

	float R = 1.0f / (float)(params.rings - 1);
	float S = 1.0f / (float)(params.sectors - 1);
	int r, s;

	for (r = 0; r < params.rings; r++){
		for (s = 0; s < params.sectors; s++) {
			float y = std::sin(-rPI_2 + rPI * r * R);
			float x = std::cos(2 * rPI * s * S) * std::sin(rPI * r * R);
			float z = std::sin(2 * rPI * s * S) * std::sin(rPI * r * R);

			position.Set(x, y + params.radius, z);
			normal = position - center;
			normal.Normalize();
			position *= params.radius;

			geometry.PushVertex(position);
			geometry.PushNormal(normal);
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