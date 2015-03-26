#include "rGeometryUtil.hpp"

unsigned short rectIndicies[] = {0, 1, 3, 1, 2, 3};

void CreateRectVerticiesWithTexCoords(const rRect& rect, rImmediateBuffer& geometry){
	geometry.PushVertex(rect.x, rect.y, 0.0f,1.0f);
	geometry.PushVertex(rect.x + rect.width, rect.y, 1.0f,1.0f);
	geometry.PushVertex(rect.x + rect.width, rect.y + rect.height, 1.0f,0.0f);
	geometry.PushVertex(rect.x , rect.y + rect.height, 0.0f,0.0f);
}

void CreateRectVerticies(const rRect& rect, rImmediateBuffer& geometry){
	geometry.PushVertex(rect.x, rect.y);
	geometry.PushVertex(rect.x + rect.width, rect.y);
	geometry.PushVertex(rect.x + rect.width, rect.y + rect.height);
	geometry.PushVertex(rect.x , rect.y + rect.height);
}

void AppendRectVerticies(const rRect& rect, rImmediateBuffer& geometry){
	unsigned short offset = geometry.VertexCount();

	CreateRectVerticies(rect, geometry);

	for (size_t i = 0; i < 6; i ++)
		geometry.PushIndex(offset + rectIndicies[i]);

}

void CircleSweep(float x, float y, float radius, float start, float end, size_t count, rImmediateBuffer& geometry){
	unsigned short centerIndex = geometry.VertexCount();
	unsigned short currentIndex = centerIndex;
	rVector2 center(x,y);

	geometry.PushVertex(center);

	float deg = start;
	float step = (end - start) / (float)count;
	rVector2 vertex;

	for (size_t i = 0; i <= count; i++){
		float rad = rMath::DegreeToRad(deg);

		vertex.Set(std::cos(rad), std::sin(rad));
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

void rGeometryUtil::CreateRectVerticies(const rRect& rect, rImmediateBuffer& geometry, bool texCoords){
	geometry.Reset(rGEOMETRY_TRIANGLES, 2, texCoords);

	geometry.SetIndexBuffer(rectIndicies, 6);
	
	if (texCoords){
		CreateRectVerticiesWithTexCoords(rect, geometry);
	}
	else{
		CreateRectVerticies(rect, geometry);
	}
}

void rGeometryUtil::CreateWireRectVerticies(const rRect& rect, rImmediateBuffer& geometry){
	static unsigned short wireRectIndicies[] = {0, 1, 1, 2, 2, 3};

	geometry.Reset(rGEOMETRY_LINE_LOOP, 2, false);
	geometry.SetIndexBuffer(wireRectIndicies, 6);

	CreateRectVerticies(rect, geometry);
}

void rGeometryUtil::CreateCircleVerticies(const rCircle2& circle, size_t segments, rImmediateBuffer& geometry){
	geometry.Reset(rGEOMETRY_TRIANGLES, 2, false);

	geometry.PushVertex(circle.center.x, circle.center.y);
	
	float step = 360.0f / (float)segments;
	unsigned short index = 1;
	
	rVector2 vertex;
	for (float angle = 0.0f; angle <= 360.0f; angle += step){
		float radians = rMath::DegreeToRad(angle);
		
		vertex.Set(std::cos(radians),std::sin(radians));
		vertex *= circle.radius;
		vertex += circle.center;
		
		geometry.PushVertex(vertex);
		
		if (index > 1){
			geometry.PushIndex(index, index - 1, 0);
		}
		
		index++;
	}

}

void rGeometryUtil::CreateWireAlignedBoxVerticies(const rAlignedBox3& box,  rImmediateBuffer& geometry){
	unsigned short indicies[] = { 0,1,1,2,2,3,3,0,4,5,5,6,6,7,7,4,0,4,1,5,2,6,3,7 };

	geometry.Reset(rGEOMETRY_LINES, 3, false);
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

void WriteWord(rFontGlyphArray& glyphs, rImmediateBuffer& geometry, int startX, int startY){
	int xPos = startX;
	int yPos = startY;

	rFontGlyph* glyph = NULL;
	for (size_t i = 0; i < glyphs.size(); i++){
		glyph = glyphs[i];

		int left = xPos + glyph->leftBearing;
		int right = left + glyph->width;
		int top = yPos - glyph->top;
		int bottom = top + glyph->height;

		size_t index = geometry.VertexCount();
		geometry.PushVertex(left, top, glyph->texCoords[0].x, glyph->texCoords[0].y);
		geometry.PushVertex(right , top, glyph->texCoords[1].x, glyph->texCoords[1].y);
		geometry.PushVertex(right, bottom , glyph->texCoords[2].x, glyph->texCoords[2].y);
		geometry.PushVertex(left, bottom, glyph->texCoords[3].x, glyph->texCoords[3].y);

		geometry.PushIndex(index, index + 1, index + 2);
		geometry.PushIndex(index, index + 2, index + 3);

		xPos += glyph->advance;
	}

	glyphs.clear();
}

void rGeometryUtil::Create2DText(const rString& str, const rFont* font, const rRect& bounding, rImmediateBuffer& geometry){
	rFontGlyphArray wordGlyphs;

	geometry.Reset(rGEOMETRY_TRIANGLES, 2, true);

	int xPos = 0;
	int yPos = font->Ascender();

	int wordWidth = 0;
	int spaceLeft = bounding.width;

	int lineCount = 0;

	for (int i = 0; i < str.size(); i++){
		int c = str[i];

		if (c == '\n'){
			if (wordWidth > spaceLeft ){ //current word will not fit on this line
				yPos += font->LineHeight();
				xPos = 0;
			}

			WriteWord(wordGlyphs, geometry, xPos, yPos);

			yPos += font->LineHeight();
			xPos = 0;
			spaceLeft = bounding.width;
			wordWidth = 0;

		}
		else{
			rFontGlyph* glyph = font->GetGlyph(c);

			if (c == ' '){
				if (wordWidth + glyph->advance > spaceLeft ){ //current word will not fit on this line
					yPos += font->LineHeight();
					xPos = 0;
					spaceLeft = bounding.width;
				}

				WriteWord(wordGlyphs, geometry, xPos, yPos);

				spaceLeft -= wordWidth + glyph->advance;
				xPos += wordWidth + glyph->advance;;
				wordWidth = 0;

			}
			else{
				wordWidth += glyph->advance;
				wordGlyphs.push_back(glyph);
			}
		}
	}

	WriteWord(wordGlyphs, geometry, xPos, yPos);
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

	pointData.Reset(rGEOMETRY_POINTS, 3, false);
	pointData.Allocate(skeleton->NumBones());
	lineData.Reset(rGEOMETRY_LINES, 3, false);
	lineData.Allocate(skeleton->NumBones());

	for (size_t i = 0; i < bones.size(); i++){
		BuildBoneGeometry(pointData, lineData, bones[i], USHRT_MAX);
	}
}

void rGeometryUtil::CreateRoundedRectVerticies(const rRect& rect, float radius, int detail, rImmediateBuffer& geometry){
	geometry.Reset(rGEOMETRY_TRIANGLES, 2, false);

	CircleSweep(rect.Right() - radius , rect.Top() + radius, radius, 0.0f, 90.0f, detail, geometry);
	CircleSweep(rect.Left() + radius , rect.Top() + radius, radius, 90.0f, 180.0f, detail, geometry);
	CircleSweep(rect.Left() + radius , rect.Bottom() - radius, radius, 180.0f, 270.0f, detail, geometry);
	CircleSweep(rect.Right() - radius , rect.Bottom() - radius, radius, 270.0f, 360.0f, detail, geometry);

	rRect r(rect.x + radius, rect.y, rect.width - (2* radius), rect.height);
	AppendRectVerticies(r, geometry);

	r.Set(rect.x, rect.y+ radius, radius, rect.height - (2* radius));
	AppendRectVerticies(r, geometry);

	r.x = rect.Right() - radius;
	AppendRectVerticies(r, geometry);
}


void rGeometryUtil::CreateCircle3d(rModelGeometryData& geometry, const rVector3& center, float radius, const rVector3& normal, size_t segmentCount){
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


void CreateConeFace(const rString& wireName, const rString& shadedName, rModelGeometryData& geometry, size_t v1, size_t v2, float coneAngle, float height){
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

void rGeometryUtil::GeneratePrimitiveCone(float baseRadius, float height, size_t segmentCount, const rString& name, rModelGeometryData& geometry){
	rString wireName = name + "_wire";
	rString shadedName = name + "_shaded";
	
	rElementBufferData* wireframe = geometry.CreateElementBuffer(wireName, rGEOMETRY_LINES);
	rElementBufferData* shaded = geometry.CreateElementBuffer(shadedName, rGEOMETRY_TRIANGLES);

	float coneAngle = std::atan(baseRadius / height);

	CreateCircle3d(geometry, rVector3::ZeroVector, baseRadius, rVector3::DownVector, segmentCount);

	for (int i = 0; i < segmentCount; i++){
		CreateConeFace(wireName, shadedName, geometry, i + 1, i + 2, coneAngle, height);
	}

	CreateConeFace(wireName, shadedName, geometry, segmentCount, 1, coneAngle, height);
}