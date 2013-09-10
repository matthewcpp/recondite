#include "rGeometryUtil.hpp"

void CreateRectVerticiesWithTexCoords(const rRect rect, rGeometryData& geometry){
	geometry.Allocate(2, 4, true, false);
	
	geometry.SetVertex(0, rect.x, rect.y, 0.0f,1.0f);
	geometry.SetVertex(1, rect.x + rect.width, rect.y, 1.0f,1.0f);
	geometry.SetVertex(2, rect.x + rect.width, rect.y + rect.height, 1.0f,0.0f);
	geometry.SetVertex(3, rect.x , rect.y + rect.height, 0.0f,0.0f);
}

void CreateRectVerticies(const rRect rect, rGeometryData& geometry){
	geometry.Allocate(2, 4, false, false);
	
	geometry.SetVertex(0, rect.x, rect.y);
	geometry.SetVertex(1, rect.x + rect.width, rect.y);
	geometry.SetVertex(2, rect.x + rect.width, rect.y + rect.height);
	geometry.SetVertex(3, rect.x , rect.y + rect.height);
}



void rGeometryUtil::CreateRectVerticies(const rRect rect, const rString& name,rGeometryData& geometry, bool texCoords){
	static unsigned short rectIndicies[] = {0, 1, 3, 1, 2, 3};
	geometry.CreateElementBuffer(name, rectIndicies, 6);
	
	if (texCoords){
		CreateRectVerticiesWithTexCoords(rect, geometry);
	}
	else{
		CreateRectVerticies(rect, geometry);
	}
}
