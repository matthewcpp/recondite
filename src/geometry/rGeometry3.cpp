#include "rGeometry3.hpp"

void rGeometry::FitAlignedBoxToSphere(rAlignedBox3& box , const rSphere3& sphere){
	box.Set(sphere.center, sphere.radius, sphere.radius, sphere.radius);
}

void rGeometry::FitSphereToAlignedBox(rSphere3& sphere , const rAlignedBox3& box){
	sphere.center = box.Center();
	sphere.radius = rMath::Max3(box.Width(), box.Height(), box.Depth());
}

void rGeometry::FitAlignedBoxToCone(rAlignedBox3& box, const rCone3& cone){
	
}
