#include "rGeometry3.hpp"

void rGeometry3::FitAlignedBoxToSphere(rAlignedBox3& box , const rSphere3& sphere){
	box.Set(sphere.center, sphere.radius, sphere.radius, sphere.radius);
}

void rGeometry3::FitSphereToAlignedBox(rSphere3& sphere , const rAlignedBox3& box){
	sphere.center = box.Center();
	sphere.radius = rMath::Max3(box.Width(), box.Height(), box.Depth());
}

void rGeometry3::FitAlignedBoxToCone(rAlignedBox3& box, const rCone3& cone){
	
}
