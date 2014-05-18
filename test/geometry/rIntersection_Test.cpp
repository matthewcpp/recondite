#include "gtest/gtest.h"

#include "rIntersection.hpp"

class Geometry_rIntersection : public ::testing::Test{
};

TEST(Geometry_rIntersection, SphereContainsBox){
	rSphere sphere(0,0,0,3);
	rAlignedBox3 box (rVector3::ZeroVector, 1,1,1);

	EXPECT_TRUE (rIntersection::SphereContainsAlignedBox(sphere,box));
}