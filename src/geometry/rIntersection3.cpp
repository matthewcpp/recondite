#include "rIntersection3.hpp"

bool rIntersection3::AlignedBoxIntersectsSphere(const rAlignedBox3& box , const rSphere3& sphere){
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

bool rIntersection3::SphereContainsAlignedBox(const rSphere3& sphere, const rAlignedBox3& box){
	return sphere.ContainsPoint(box.max) && sphere.ContainsPoint(box.min);
}

bool rIntersection3::AlignedBoxContainsSphere(const rAlignedBox3& box , const rSphere3& sphere){
	return	sphere.center.x + sphere.radius <= box.max.x &&
			sphere.center.y + sphere.radius <= box.max.y &&
			sphere.center.z + sphere.radius <= box.max.z &&

			sphere.center.x - sphere.radius >= box.min.x &&
			sphere.center.y - sphere.radius >= box.min.y &&
			sphere.center.z - sphere.radius >= box.min.z;
}

bool rIntersection3::RayIntersectsPlane(const rRay3& ray , const rPlane3& plane, rVector3* point){
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

bool rIntersection3::RayIntersectsAlignedBox(const rRay3& ray,const rAlignedBox3& box ){
	if (box.ContainsPoint(ray.origin))
		return true;

	rVector3 corners[8];
	rVector3 point;
	rPlane3 plane;
	box.GetCorners(corners);

	//test the front
	plane.Set(rVector3::ForwardVector , box.max.z);
	if(rIntersection3::RayIntersectsPlane(ray , plane, &point) && rMath::PointInBoundedXYPlane(corners[0] , corners[2], point))
		return true;

	//test the back
	plane.Set(rVector3::BackwardVector , box.min.z);
	if(rIntersection3::RayIntersectsPlane(ray , plane, &point) && rMath::PointInBoundedXYPlane(corners[4] , corners[6], point))
		return true;

	//test the top
	plane.Set(rVector3::UpVector , box.max.y);
	if(rIntersection3::RayIntersectsPlane(ray , plane, &point) && rMath::PointInBoundedXZPlane(corners[0] , corners[5], point))
		return true;

	//test the bottom
	plane.Set(rVector3::DownVector,  box.min.y);
	if(rIntersection3::RayIntersectsPlane(ray , plane, &point) && rMath::PointInBoundedXZPlane(corners[3] , corners[6], point))
		return true;
	

	//test the right
	plane.Set(rVector3::RightVector , box.max.x);
	if(rIntersection3::RayIntersectsPlane(ray , plane, &point) && rMath::PointInBoundedYZPlane(corners[1] , corners[6], point))
		return true;

	//test the left
	plane.Set(rVector3::LeftVector, box.min.x);
	if(rIntersection3::RayIntersectsPlane(ray , plane, &point) && rMath::PointInBoundedYZPlane(corners[0] , corners[7], point))
		return true;


	return false;
}

bool rIntersection3::RayIntersectsSphere(const rRay3& ray , const rSphere3& sphere){
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