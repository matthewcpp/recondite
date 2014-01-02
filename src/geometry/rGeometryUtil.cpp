#include "rGeometryUtil.hpp"

void CreateRectVerticiesWithTexCoords(const rRect& rect, rGeometryData& geometry){
	geometry.Allocate(2, 4, true, false);
	
	geometry.SetVertex(0, rect.x, rect.y, 0.0f,1.0f);
	geometry.SetVertex(1, rect.x + rect.width, rect.y, 1.0f,1.0f);
	geometry.SetVertex(2, rect.x + rect.width, rect.y + rect.height, 1.0f,0.0f);
	geometry.SetVertex(3, rect.x , rect.y + rect.height, 0.0f,0.0f);
}

void CreateRectVerticies(const rRect& rect, rGeometryData& geometry){
	geometry.Allocate(2, 4, false, false);
	
	geometry.SetVertex(0, rect.x, rect.y);
	geometry.SetVertex(1, rect.x + rect.width, rect.y);
	geometry.SetVertex(2, rect.x + rect.width, rect.y + rect.height);
	geometry.SetVertex(3, rect.x , rect.y + rect.height);
}

void rGeometryUtil::CreateRectVerticies(const rRect& rect, const rString& name,rGeometryData& geometry, bool texCoords){
	static unsigned short rectIndicies[] = {0, 1, 3, 1, 2, 3};
	geometry.CreateElementBuffer(name, rectIndicies, 6, rGEOMETRY_TRIANGLES);
	
	if (texCoords){
		CreateRectVerticiesWithTexCoords(rect, geometry);
	}
	else{
		CreateRectVerticies(rect, geometry);
	}
}

void rGeometryUtil::CreateWireRectVerticies(const rRect& rect, const rString& name, rGeometryData& geometry){
	static unsigned short wireRectIndicies[] = {0, 1, 1, 2, 2, 3};
	geometry.CreateElementBuffer(name, wireRectIndicies, 6, rGEOMETRY_LINE_LOOP);

	CreateRectVerticies(rect, geometry);
}

void rGeometryUtil::CreateCircleVerticies(const rCircle2& circle, size_t segments, const rString& name, rGeometryData& geometry){

	geometry.Allocate(2, segments + 2, false, false);
	rElementBufferData* buffer = geometry.CreateElementBuffer(name);
	

	geometry.SetVertex(0, circle.center.x, circle.center.y);
	
	float step = 360.0f / (float)segments;
	unsigned short index = 1;
	
	rVector2 vertex;
	for (float angle = 0.0f; angle <= 360.0f; angle += step){
		float radians = rMath::DegreeToRad(angle);
		
		vertex.Set(std::cos(radians),std::sin(radians));
		vertex *= circle.radius;
		vertex += circle.center;
		
		geometry.SetVertex(index, vertex);
		
		if (index > 1){
			buffer->Push(index, index - 1, 0);
		}
		
		index++;
	}

}

void rGeometryUtil::CreateWireAlignedBoxVerticies(const rAlignedBox3& box, const rString& name, rGeometryData& geometry){
	unsigned short indicies[] = { 0,1,1,2,2,3,3,0,4,5,5,6,6,7,7,4,0,4,1,5,2,6,3,7 };
	geometry.CreateElementBuffer(name, indicies, 24, rGEOMETRY_LINES);

	geometry.Allocate(3, 8, false, false);

	geometry.SetVertex(0,box.min.x, box.max.y, box.max.z);
	geometry.SetVertex(1,box.max.x, box.max.y, box.max.z);
	geometry.SetVertex(2,box.max.x, box.min.y, box.max.z);
	geometry.SetVertex(3,box.min.x, box.min.y, box.max.z);

	geometry.SetVertex(4,box.min.x, box.max.y, box.min.z);
	geometry.SetVertex(5,box.max.x, box.max.y, box.min.z);
	geometry.SetVertex(6,box.max.x, box.min.y, box.min.z);
	geometry.SetVertex(7,box.min.x, box.min.y, box.min.z);
}

void WriteWord(rFontGlyphArray& glyphs, rGeometryData& geometry, int startX, int startY){
	rElementBufferData* elements = geometry.GetElementBuffer("immediate");

	int xPos = startX;
	int yPos = startY;

	rFontGlyph* glyph = NULL;
	for (size_t i = 0; i < glyphs.size(); i++){
		glyph = glyphs[i];

		int left = xPos + glyph->leftBearing;
		int right = left + glyph->width;
		int top = yPos - glyph->top;
		int bottom = top + glyph->height;

		unsigned short index = geometry.Push(left, top, glyph->texCoords[0].x, glyph->texCoords[0].y);
		geometry.Push(right , top, glyph->texCoords[1].x, glyph->texCoords[1].y);
		geometry.Push(right, bottom , glyph->texCoords[2].x, glyph->texCoords[2].y);
		geometry.Push(left, bottom, glyph->texCoords[3].x, glyph->texCoords[3].y);

		elements->Push(index, index + 1, index + 2);
		elements->Push(index, index + 2, index + 3);

		xPos += glyph->advance;
	}

	glyphs.clear();
}

void rGeometryUtil::Create2DText(const rString& str, const rFont* font, const rRect& bounding, const rString& name, rGeometryData& geometry){
	rFontGlyphArray wordGlyphs;

	geometry.SetVertexDataInfo(2, true, false);
	rElementBufferData* elements = geometry.CreateElementBuffer(name);

	int xPos = 0;
	int yPos = font->LineHeight();

	int wordWidth = 0;
	int spaceLeft = bounding.width;

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

void BuildBoneGeometry(rGeometryData& geometryData, rBone* bone, unsigned short parentVertexIndex){
	geometryData.SetVertex(bone->id, bone->WoldPosition());
	geometryData.GetElementBuffer("skeleton_points")->Push(bone->id);

	if (parentVertexIndex != USHRT_MAX){
		geometryData.GetElementBuffer("skeleton_wire")->Push(parentVertexIndex, bone->id);
	}

	for (size_t i = 0; i < bone->children.size(); i++){
		BuildBoneGeometry(geometryData, bone->children[i], bone->id);
	}
}

void rGeometryUtil::CreateSkeletonGeometry(const rSkeleton* skeleton, const rString& name, rGeometryData& geometryData){
	rBoneArray bones;
	skeleton->GetTopLevelBones(bones);

	geometryData.Allocate(3, skeleton->NumBones(), false, false);

	geometryData.CreateElementBuffer(name + "_wire")->SetGeometryType(rGEOMETRY_LINES);
	geometryData.CreateElementBuffer(name + "_points")->SetGeometryType(rGEOMETRY_POINTS);

	for (size_t i = 0; i < bones.size(); i++){
		BuildBoneGeometry(geometryData, bones[i], USHRT_MAX);
	}
}
