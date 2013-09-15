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
	geometry.CreateElementBuffer(name, rectIndicies, 6);
	
	if (texCoords){
		CreateRectVerticiesWithTexCoords(rect, geometry);
	}
	else{
		CreateRectVerticies(rect, geometry);
	}
}

void rGeometryUtil::CreateCircleVerticies(const rCircle2& circle, size_t segments, const rString& name, rGeometryData& geometry){
	geometry.Allocate(2, segments + 1, false, false);
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
