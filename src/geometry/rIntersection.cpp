#include "rIntersection.hpp"

bool rIntersection::AlignedBoxIntersectsSphere(const rAlignedBox3& box , const rSphere& sphere){
	rVector3 r;

	if (sphere.center.x < box.min.x) {
		r.x =  box.min.x;
	} else if (sphere.center.x >  box.max.x) {
		r.x =  box.max.x;
	} else {
		r.x = sphere.center.x;
	}

	if (sphere.center.y < box.min.y) {
		r.y =  box.min.y;
	} else if (sphere.center.y >  box.max.y) {
		r.y =  box.max.y;
	} else {
		r.y = sphere.center.y;
	}

	if (sphere.center.z <  box.min.z) {
		r.z =  box.min.z;
	} else if (sphere.center.z >  box.max.z) {
		r.z =  box.max.z;
	} else {
		r.z = sphere.center.z;
	}

	return r.Distance(sphere.center) <= sphere.radius;
}

bool rIntersection::SphereContainsAlignedBox(const rSphere& sphere, const rAlignedBox3& box){
	return sphere.ContainsPoint(box.max) && sphere.ContainsPoint(box.min);
}

bool rIntersection::AlignedBoxContainsSphere(const rAlignedBox3& box , const rSphere& sphere){
	return	sphere.center.x + sphere.radius <= box.max.x &&
			sphere.center.y + sphere.radius <= box.max.y &&
			sphere.center.z + sphere.radius <= box.max.z &&

			sphere.center.x - sphere.radius >= box.min.x &&
			sphere.center.y - sphere.radius >= box.min.y &&
			sphere.center.z - sphere.radius >= box.min.z;
}

bool rIntersection::RayIntersectsPlane(const rRay3& ray , const rPlane& plane, rVector3* point){
	float dist_dot_normal = plane.normal.Dot(ray.direction);
	float signedDistance =  plane.DistanceToPoint(ray.origin);
	float rayParam = -signedDistance / dist_dot_normal;

	if (rayParam >= 0 && std::fabs(dist_dot_normal) > 0.0f){
		if (point){
			rVector3 tv = ray.direction * rayParam;
			point->Set(ray.origin.x + tv.x , ray.origin.y + tv.y, ray.origin.z + tv.z);
		}

		return true;
	}

	if (rayParam >= 0 && std::fabs(signedDistance) <= 0.0f){
		if (point)
			*point = ray.origin;
		
		return true;
	}
	

	return false;
}

bool rIntersection::RayIntersectsAlignedBox(const rRay3& ray,const rAlignedBox3& box ){
	if (box.ContainsPoint(ray.origin))
		return true;


	return false;
}

bool rIntersection::RayIntersectsSphere(const rRay3& ray , const rSphere& sphere){
	if (sphere.ContainsPoint(ray.origin))
		return true;

	rVector3 org_center = ray.origin - sphere.center;

	float a = ray.direction.Dot(ray.direction);
	float b = 2 * (ray.direction.Dot(org_center));
	float c = org_center.Dot(org_center) - std::pow(sphere.radius, 2.0f);

	float discriminant = b * b - (4.0f * a * c);

	if (discriminant < 0.0f)
		return false;

	return true;
}

bool FrustrumPlaneSphereCheck(const rPlane& plane, const rSphere& sphere, int& planeCount){


	return true;
}

int FrustrumSphereTest(const rFrustrum& frustrum, const rSphere& sphere){
	int planeCount = 0;
	float distance;

	distance = frustrum.pNear.DistanceToPoint(sphere.center);
	if (distance <= -sphere.radius) 
		return 0;
	if (distance > sphere.radius)
		planeCount++;

	distance = frustrum.pFar.DistanceToPoint(sphere.center);
	if (distance <= -sphere.radius) 
		return 0;
	if (distance > sphere.radius)
		planeCount++;

	distance = frustrum.pLeft.DistanceToPoint(sphere.center);
	if (distance <= -sphere.radius) 
		return 0;
	if (distance > sphere.radius)
		planeCount++;

	distance = frustrum.pRight.DistanceToPoint(sphere.center);
	if (distance <= -sphere.radius) 
		return 0;
	if (distance > sphere.radius)
		planeCount++;

	distance = frustrum.pTop.DistanceToPoint(sphere.center);
	if (distance <= -sphere.radius) 
		return 0;
	if (distance > sphere.radius)
		planeCount++;

	distance = frustrum.pBottom.DistanceToPoint(sphere.center);
	if (distance <= -sphere.radius) 
		return 0;
	if (distance > sphere.radius)
		planeCount++;

	return planeCount;
}

bool rIntersection::FrustrumContainsSphere(const rFrustrum& frustrum, const rSphere& sphere){
	return FrustrumSphereTest(frustrum, sphere) == 6;
}

bool rIntersection::FrustrumIntersectsSphere(const rFrustrum& frustrum, const rSphere& sphere){
	return FrustrumSphereTest(frustrum, sphere) > 0;
}