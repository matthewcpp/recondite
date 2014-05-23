#include "gtest/gtest.h"

#include "rGeometry_Test_Common.hpp"

#include "rFrustrum.hpp"

class Geometry_rFrustrum : public ::testing::Test{
};

TEST(Geometry_rFrustrum, PointInPlane){
	float scale =  10.0f;
	rFrustrum f;
	InitBasicFrustrum(f, scale);
	
	EXPECT_TRUE(f.PointInFrustrum(rVector3::ZeroVector));
	EXPECT_TRUE(f.PointInFrustrum(rVector3(1,-1,-1)));

	EXPECT_FALSE(f.PointInFrustrum(rVector3(1,1000,0)));
}
