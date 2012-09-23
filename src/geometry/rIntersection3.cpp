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

#define INTERSECT_NONE 0
#define INTERSECT_POINT 1
#define INTERSECT_SEGMENT 2
#define INTERSECT_RAY 3

int rIntersection3::RayIntersectsCone(const rRay3& ray , const rCone3& cone){
	float cosAngle = std::cos(cone.angle);
    float cosSquadred = cosAngle * cosAngle;

	float cone_dir_dot_line_dir = cone.direction.Dot(ray.direction);
	
	rVector3 e = ray.origin - cone.point;
    float e_dot_e = e.Dot(e);

	float cone_dir_dot_e = cone.direction.Dot(e);
	float ray_dir_dot_e = ray.direction.Dot(e);
	

	float c2 = cone_dir_dot_line_dir * cone_dir_dot_line_dir - cosSquadred;
	float c1 = cone_dir_dot_line_dir * cone_dir_dot_e - cosSquadred * ray_dir_dot_e;
	float c0 = cone_dir_dot_e * cone_dir_dot_e - cosSquadred * e_dot_e;

	float dot;

	int intersectCount = 0;
	int intersectionType = 0;

	rVector3 intersectPoints[2];

	// Solve the quadratic.  Keep only those X for which Dot(A,X-V) >= 0.
	if (std::fabs(c2) >= 0.0f){

		float discriminat = c1 * c1 - c0 * c2;

		//solve quadratic fomula
		if (discriminat < 0.0f){ // no intersections
			intersectCount = 0;
			intersectionType = INTERSECT_NONE;
		}
		else if (discriminat > 0.0f){ //2 possible roots
			float root = std::sqrt(discriminat);
			float inv_c2 = 1.0f / c2;

			float t = (-c1 - root) * inv_c2;
			intersectPoints[intersectCount] = ray.origin + (ray.direction * t);
			e = intersectPoints[intersectCount] - cone.point;
			dot = e.Dot(cone.direction);

			if (dot > 0.0f)
				intersectCount++;

			t = (-c1 + root) * inv_c2;
			intersectPoints[intersectCount] = ray.origin + (ray.direction * t);
			e = intersectPoints[intersectCount] - cone.point;
			dot = e.Dot(cone.direction);

			if (dot > 0.0f)
				intersectCount++;

			if (intersectCount == 2)
				intersectionType = INTERSECT_SEGMENT;
			else if (intersectCount == 1){
				intersectionType = INTERSECT_RAY;
				intersectPoints[intersectCount] = ray.direction;
			}
			else
				intersectionType = INTERSECT_NONE;

		}
		else{ // 1 possible root
			float t = (c1/c2);
			intersectPoints[intersectCount]= ray.origin + (ray.direction * t);
			e = intersectPoints[intersectCount] - cone.point;

			if (e.Dot(cone.direction) > 0.0f ){
				intersectCount = 1;
				intersectionType = INTERSECT_POINT;
			}
			else{
				intersectCount = 0;
				intersectionType = INTERSECT_NONE;
			}
		}

	}
	else if (std::fabs(c1) >= 0.0f){
		 // c2 = 0, c1 != 0 (D is a direction vector on the cone boundary)
		float t =(0.5f * c0)/ c1;
		intersectPoints[0] = ray.origin + (ray.direction * t);
		e = intersectPoints[0] - cone.point;

		dot = e.Dot(cone.direction);
		if (dot > 0.0f){
			intersectionType = INTERSECT_RAY;
			intersectCount = 2;
			intersectPoints[1] = ray.direction;
		}
		else{
			intersectCount = 0;
			intersectionType = INTERSECT_NONE;
		}
		
	}
	else if (std::fabs(c0) >= 0.0f){
		 // c2 = c1 = 0, c0 != 0
		intersectCount = 0;
		intersectionType = INTERSECT_NONE;
	}
	else{
		// c2 = c1 = c0 = 0, cone contains ray V+t*D where V is cone vertex and D is the line direction.
        intersectPoints[0] = cone.point;
        intersectPoints[1] = ray.direction;
		intersectCount = 2;
		intersectionType = INTERSECT_RAY;
	}

	wxLogMessage ("Intersection Type: %i" , intersectionType);
	if (intersectionType == INTERSECT_SEGMENT){
		rVector3 b = cone.Base();
		rPlane3 cap(cone.direction , 0.0f);
		cap.d = cap.DistanceToPoint(b);
		wxLogMessage("Cone Base [%f %f %f]", b.x , b.y , b.z);
		wxLogMessage("Plane: [%f %f %f] %f" ,cap.normal.x , cap.normal.y , cap.normal.z , cap.d );
		wxLogMessage("Segment: [%f %f %f] [%f %f %f]", intersectPoints[0].x , intersectPoints[0].y , intersectPoints[0].z, intersectPoints[1].x , intersectPoints[1].y , intersectPoints[1].z);
		
		return cap.Side (intersectPoints[0] ) == -1 &&  cap.Side(intersectPoints[1]  ) ==  -1;
	}

	return intersectionType != INTERSECT_NONE;
}