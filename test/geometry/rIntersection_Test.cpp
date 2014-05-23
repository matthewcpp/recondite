#include "gtest/gtest.h"

#include "rIntersection.hpp"
#include "rGeometry_Test_Common.hpp"

class Geometry_rIntersection : public ::testing::Test{
};

TEST(Geometry_rIntersection, SphereContainsBox){
	rSphere sphere(0,0,0,3);
	rAlignedBox3 box (rVector3::ZeroVector, 1,1,1);

	EXPECT_TRUE (rIntersection::SphereContainsAlignedBox(sphere,box));
}

TEST(Geometry_rIntersection, FrustrumContainsSphere){
	rFrustrum f;
	InitBasicFrustrum(f, 10);

	rSphere s(rVector3::ZeroVector ,1);
	EXPECT_TRUE(rIntersection::FrustrumContainsSphere(f,s));

	s.Set(1,1,1,2);
	EXPECT_TRUE(rIntersection::FrustrumContainsSphere(f,s));

	s.radius = 100;
	EXPECT_FALSE(rIntersection::FrustrumContainsSphere(f,s));

	s.Set(-100,-100,-100, 10);
	EXPECT_FALSE(rIntersection::FrustrumContainsSphere(f,s));
}

TEST(Geometry_rIntersection, FrustrumIntersectsSphere){
	rFrustrum f;
	InitBasicFrustrum(f, 10);

	rSphere s(rVector3::ZeroVector ,1);
	EXPECT_TRUE(rIntersection::FrustrumIntersectsSphere(f,s));

	s.Set(1,1,1,2);
	EXPECT_TRUE(rIntersection::FrustrumIntersectsSphere(f,s));

	s.radius = 200;
	EXPECT_FALSE(rIntersection::FrustrumIntersectsSphere(f,s));
}

TEST(Geometry_rIntersection, RayBoxIntersection){
	rRay3 ray(rVector3(0, 0 , 101), rVector3::ForwardVector);
	rAlignedBox3 box(rVector3::OneVector * 100 , rVector3::OneVector * -100);

	EXPECT_TRUE(rIntersection::RayIntersectsAlignedBox(ray, box));
	ray.direction.Set(0,0.001,- 0.001);
	ray.direction.Normalize();

	EXPECT_TRUE(rIntersection::RayIntersectsAlignedBox(ray, box));
}