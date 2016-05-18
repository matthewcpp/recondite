#include "rGeometryUtil.hpp"

unsigned short rectIndicies[] = {0, 1, 3, 1, 2, 3};
unsigned short wireRectIndicies[] = { 0, 1, 1, 2, 2, 3, 3, 0 };

void CreateRectVerticiesWithTexCoords(const rRect& rect, rImmediateBuffer& geometry, float zValue){
	geometry.PushVertex(rect.x, rect.y, zValue, 0.0f, 1.0f);
	geometry.PushVertex(rect.x + rect.width, rect.y, zValue, 1.0f,1.0f);
	geometry.PushVertex(rect.x + rect.width, rect.y + rect.height, zValue, 1.0f, 0.0f);
	geometry.PushVertex(rect.x , rect.y + rect.height, zValue, 0.0f, 0.0f);
}

void CreateRectVerticies(const rRect& rect, rImmediateBuffer& geometry, float zValue){
	geometry.PushVertex(rect.x, rect.y, zValue);
	geometry.PushVertex(rect.x + rect.width, rect.y, zValue);
	geometry.PushVertex(rect.x + rect.width, rect.y + rect.height, zValue);
	geometry.PushVertex(rect.x , rect.y + rect.height, zValue);
}

void AppendRectVerticies(const rRect& rect, rImmediateBuffer& geometry, float zValue){
	unsigned short offset = geometry.VertexCount();

	CreateRectVerticies(rect, geometry, zValue);

	for (size_t i = 0; i < 6; i ++)
		geometry.PushIndex(offset + rectIndicies[i]);

}

void CircleSweep(float x, float y, float radius, float start, float end, size_t count, rImmediateBuffer& geometry, float zValue){
	unsigned short centerIndex = geometry.VertexCount();
	unsigned short currentIndex = centerIndex;
	rVector3 center(x,y, zValue);

	geometry.PushVertex(center);

	float deg = start;
	float step = (end - start) / (float)count;
	rVector3 vertex;

	for (size_t i = 0; i <= count; i++){
		float rad = rMath::DegreeToRad(deg);

		vertex.Set(std::cos(rad), std::sin(rad), 0.0);
		vertex.x *= radius;
		vertex.y *= -radius;
		vertex = center + vertex;

		geometry.PushVertex(vertex);
		currentIndex += 1;

		if (count){
			geometry.PushIndex(centerIndex, currentIndex - 1, currentIndex);
		}
		
		deg += step;

		if (deg > end)
			deg = end;
	}
}

bool rGeometryUtil::CreateRectVerticies(const rRect& rect, rImmediateBuffer& geometry, bool texCoords, float zValue){
	if (geometry.GeometryType() != rGeometryType::Triangles) return false;
	if (texCoords && !geometry.HasTexCoords()) return false;

	uint16_t baseIndex = (uint16_t)geometry.VertexCount();
	for (uint16_t i = 0; i < 6; i++){
		geometry.PushIndex(rectIndicies[i] + baseIndex);
	}
	
	if (texCoords){
		CreateRectVerticiesWithTexCoords(rect, geometry, zValue);
	}
	else{
		CreateRectVerticies(rect, geometry, zValue);
	}

	return true;
}

bool rGeometryUtil::CreateWireRectVerticies(const rRect& rect, rImmediateBuffer& geometry, float zValue){
	if (geometry.GeometryType() != rGeometryType::Lines) return false;

	uint16_t baseIndex = (uint16_t)geometry.VertexCount();
	for (uint16_t i = 0; i < 8; i++){
		geometry.PushIndex(wireRectIndicies[i] + baseIndex);
	}

	CreateRectVerticies(rect, geometry, zValue);

	return true;
}

bool rGeometryUtil::CreateCircleVerticies(const rCircle2& circle, size_t segments, rImmediateBuffer& geometry, float zValue){
	if (geometry.GeometryType() != rGeometryType::Triangles) return false;


	geometry.PushVertex(circle.center.x, circle.center.y);
	
	float step = 360.0f / (float)segments;
	unsigned short index = 1;
	
	rVector3 vertex;
	rVector3 circleCenter(circle.center.x, circle.center.y, zValue);

	for (float angle = 0.0f; angle <= 360.0f; angle += step){
		float radians = rMath::DegreeToRad(angle);
		
		vertex.Set(std::cos(radians),std::sin(radians), 0.0f);
		vertex *= circle.radius;
		vertex += circleCenter;
		
		geometry.PushVertex(vertex);
		
		if (index > 1){
			geometry.PushIndex(index, index - 1, 0);
		}
		
		index++;
	}


	return true;
}

void rGeometryUtil::CreateWireAlignedBoxVerticies(const rAlignedBox3& box,  rImmediateBuffer& geometry){
	unsigned short indicies[] = { 0,1,1,2,2,3,3,0,4,5,5,6,6,7,7,4,0,4,1,5,2,6,3,7 };

	geometry.Reset(rGeometryType::Lines, 3, false);
	geometry.SetIndexBuffer(indicies, 24);

	geometry.PushVertex(box.min.x, box.max.y, box.max.z);
	geometry.PushVertex(box.max.x, box.max.y, box.max.z);
	geometry.PushVertex(box.max.x, box.min.y, box.max.z);
	geometry.PushVertex(box.min.x, box.min.y, box.max.z);

	geometry.PushVertex(box.min.x, box.max.y, box.min.z);
	geometry.PushVertex(box.max.x, box.max.y, box.min.z);
	geometry.PushVertex(box.max.x, box.min.y, box.min.z);
	geometry.PushVertex(box.min.x, box.min.y, box.min.z);
}



void rGeometryUtil::Create2DText(const rString& str, const Font::Face* font, const rRect& bounding, rImmediateBuffer& geometry){
	
}

void BuildBoneGeometry(rImmediateBuffer& pointData, rImmediateBuffer& lineData, rBone* bone, unsigned short parentVertexIndex){
	rVector3 worldPos = bone->WoldPosition();
	size_t index = bone->id;

	lineData.SetVertex(index, worldPos);
	pointData.SetVertex(index, worldPos);
	pointData.PushIndex(index);

	if (parentVertexIndex != USHRT_MAX){
		lineData.PushIndex(index, parentVertexIndex);
	}

	for (size_t i = 0; i < bone->children.size(); i++){
		BuildBoneGeometry(pointData, lineData, bone->children[i], index);
	}
}

void rGeometryUtil::CreateSkeletonGeometry(const rSkeleton* skeleton, rImmediateBuffer& pointData, rImmediateBuffer& lineData){
	rBoneArray bones;
	skeleton->GetTopLevelBones(bones);

	pointData.Reset(rGeometryType::Points, 3, false);
	pointData.Allocate(skeleton->NumBones());
	lineData.Reset(rGeometryType::Lines, 3, false);
	lineData.Allocate(skeleton->NumBones());

	for (size_t i = 0; i < bones.size(); i++){
		BuildBoneGeometry(pointData, lineData, bones[i], USHRT_MAX);
	}
}

bool rGeometryUtil::CreateRoundedRectVerticies(const rRect& rect, float radius, int detail, rImmediateBuffer& geometry, float zValue){
	if (geometry.GeometryType() != rGeometryType::Triangles) return false;

	CircleSweep(rect.Right() - radius , rect.Top() + radius, radius, 0.0f, 90.0f, detail, geometry, zValue);
	CircleSweep(rect.Left() + radius , rect.Top() + radius, radius, 90.0f, 180.0f, detail, geometry, zValue);
	CircleSweep(rect.Left() + radius , rect.Bottom() - radius, radius, 180.0f, 270.0f, detail, geometry, zValue);
	CircleSweep(rect.Right() - radius , rect.Bottom() - radius, radius, 270.0f, 360.0f, detail, geometry, zValue);

	rRect r(rect.x + radius, rect.y, rect.width - (2* radius), rect.height);
	AppendRectVerticies(r, geometry, zValue);

	r.Set(rect.x, rect.y+ radius, radius, rect.height - (2* radius));
	AppendRectVerticies(r, geometry, zValue);

	r.x = rect.Right() - radius;
	AppendRectVerticies(r, geometry, zValue);

	return true;
}


void rGeometryUtil::CreateCircle3d(rTexCoordGeometryData& geometry, const rVector3& center, float radius, const rVector3& normal, size_t segmentCount){
	rElementBufferData* wireframe = geometry.GetElementBuffer("wire");
	rElementBufferData* shaded = geometry.GetElementBuffer("shaded");

	float step = 360.0f / (float)segmentCount;

	rVector3 position;
	rVector2 texCoord = rVector2::ZeroVector;

	size_t baseIndex = geometry.VertexCount();
	geometry.PushVertex(center, normal, texCoord);

	for (int i = 0; i < segmentCount; i++){
		float angle = float(i) * step;
		float radians = rMath::DegreeToRad(angle);

		position.Set(std::cos(radians), 0.0f, std::sin(radians));
		position *= radius;
		position += center;

		geometry.PushVertex(position, normal, texCoord);

		if (i > 0){
			wireframe->Push(baseIndex + i, baseIndex + i + 1);
			shaded->Push(baseIndex, baseIndex + i, baseIndex + i + 1);
		}
	}

	wireframe->Push(baseIndex + segmentCount, baseIndex + 1);
	shaded->Push(baseIndex, baseIndex + segmentCount, baseIndex + 1);
}


void CreateConeFace(const rString& wireName, const rString& shadedName, rTexCoordGeometryData& geometry, size_t v1, size_t v2, float coneAngle, float height){
	rElementBufferData* wireframe = geometry.GetElementBuffer(wireName);
	rElementBufferData* shaded = geometry.GetElementBuffer(shadedName);

	rVector3 tip = rVector3::UpVector * height;
	rVector3 p1, p2, n1, n2;

	geometry.GetVertex(v1, &p1, NULL, NULL);
	n1 = p1.GetNormalized();
	n1 *= std::cos(coneAngle);
	n1.y = std::sin(coneAngle);

	geometry.GetVertex(v2, &p2, NULL, NULL);
	n2 = p1.GetNormalized();
	n2 *= std::cos(coneAngle);
	n2.y = std::sin(coneAngle);

	size_t baseIndex = geometry.VertexCount();
	geometry.PushVertex(tip, n1, rVector2::ZeroVector);
	geometry.PushVertex(p1, n1, rVector2::ZeroVector);
	geometry.PushVertex(p2, n2, rVector2::ZeroVector);
	shaded->Push(baseIndex, baseIndex + 1, baseIndex + 2);

	wireframe->Push(baseIndex, baseIndex + 1);
	wireframe->Push(baseIndex, baseIndex + 2);
}

void rGeometryUtil::GeneratePrimitiveCone(float baseRadius, float height, size_t segmentCount, const rString& name, rTexCoordGeometryData& geometry){
	rString wireName = name + "_wire";
	rString shadedName = name + "_shaded";
	
	rElementBufferData* wireframe = geometry.CreateElementBuffer(wireName, rGeometryType::Lines);
	rElementBufferData* shaded = geometry.CreateElementBuffer(shadedName, rGeometryType::Triangles);

	float coneAngle = std::atan(baseRadius / height);

	CreateCircle3d(geometry, rVector3::ZeroVector, baseRadius, rVector3::DownVector, segmentCount);

	for (int i = 0; i < segmentCount; i++){
		CreateConeFace(wireName, shadedName, geometry, i + 1, i + 2, coneAngle, height);
	}

	CreateConeFace(wireName, shadedName, geometry, segmentCount, 1, coneAngle, height);
}