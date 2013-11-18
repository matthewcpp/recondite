#include "rMathUtil.hpp"

float rMath::DegreeToRad(float deg){
	return deg * (M_PI / 180.0f);
}

float rMath::RadToDeg(float rad){
	return rad * (180.0f / M_PI);
}

float rMath::ConvertRange(float value, float inMin, float inMax, float outMin, float outMax){
    return outMin + ((value - inMin) / (inMax - inMin)) * (outMax - outMin);
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