#include "rMathUtil.hpp"

void rMath::Matrix3TransformRectangle(const rMatrix3& m , rRectangle2& r){
	rVector2 tl = r.TopLeft();
	rVector2 br = r.BottomRight();
	m.TransformVector2(tl);
	m.TransformVector2(br);
	r.Set(tl,br);
}

void rMath::Matrix3TransformCircle(const rMatrix3& m , rCircle2& c){
	m.TransformVector2(c.center);
	c.radius *= 1.0f + (1.0f - m.m[0]);
}

float rMath::DegreeToRad(float deg){
	return deg * float(M_PI / 180.0f);
}

float rMath::Max3(float n1 , float n2, float n3){
	if (n1 > n2){
		if (n1 > n3)
			return n1;
		else
			return n3;
	}
	else{
		if (n2 > n3)
			return n2;
	}
	
	return n3;
}

rVector2 rMath::ClosestPointOnSegment(const rLineSegment2& ls , const rCircle2& c){
	rVector2 segV = ls.s2 - ls.s1 ;
	rVector2 segN = rVector2::Normalize(segV);

	rVector2 ptV = c.center -  ls.s1;

	float projL = ptV.Dot(segN);

	if (projL < 0)
		return ls.s1;

	if (projL > segV.Length())
		return ls.s2;

	rVector2 projV = segN * projL;

	return ls.s1 + projV;
}

bool rMath::PointInBoundedXYPlane(const rVector3& corner1 , const rVector3& corner2 , const rVector3& point){
	float minX = std::min(corner1.x , corner2.x);
	float minY = std::min(corner1.y , corner2.y);
	float maxX = std::max(corner1.x , corner2.x);
	float maxY = std::max(corner1.y , corner2.y);

	return	point.x >= minX && point.x <= maxX && 
			point.y >= minY && point.y <= maxY;
}

bool rMath::PointInBoundedXZPlane(const rVector3& corner1 , const rVector3& corner2 , const rVector3& point){
	float minX = std::min(corner1.x , corner2.x);
	float minZ = std::min(corner1.z , corner2.z);
	float maxX = std::max(corner1.x , corner2.x);
	float maxZ = std::max(corner1.z , corner2.z);

	return	point.x >= minX && point.x <= maxX && 
			point.z >= minZ && point.z <= maxZ;
}

bool rMath::PointInBoundedYZPlane(const rVector3& corner1 , const rVector3& corner2 , const rVector3& point){

	float minY = std::min(corner1.y , corner2.y);
	float minZ = std::min(corner1.z , corner2.z);
	float maxY = std::max(corner1.y , corner2.y);
	float maxZ = std::max(corner1.z , corner2.z);

	return	point.y >= minY && point.y <= maxY &&
			point.z >= minZ && point.z <= maxZ;
}