#include "gtest/gtest.h"

#include "rFrustrum.hpp"

class Geometry_rFrustrum : public ::testing::Test{
};

TEST(Geometry_rFrustrum, PointInPlane){
	float scale =  10.0f;
	rFrustrum f;
	
	f.near.SetFromPointAndNormal(rVector3::BackwardVector * scale, rVector3::ForwardVector);
	f.far.SetFromPointAndNormal(rVector3::ForwardVector * scale, rVector3::BackwardVector);
	f.left.SetFromPointAndNormal(rVector3::LeftVector * scale, rVector3::RightVector);
	f.right.SetFromPointAndNormal(rVector3::RightVector * scale, rVector3::LeftVector);
	f.top.SetFromPointAndNormal(rVector3::UpVector * scale, rVector3::DownVector);
	f.bottom.SetFromPointAndNormal(rVector3::DownVector * scale, rVector3::UpVector);

	EXPECT_TRUE(f.PointInFrustrum(rVector3::ZeroVector));
	EXPECT_TRUE(f.PointInFrustrum(rVector3(1,-1,-1)));

	EXPECT_FALSE(f.PointInFrustrum(rVector3(1,1000,0)));
}
