#include "gtest/gtest.h"

#include "rFrustrum.hpp"

class Geometry_rFrustrum : public ::testing::Test{
};

TEST(Geometry_rFrustrum, PointInPlane){
	float scale =  10.0f;
	rFrustrum f;
	
	f.pNear.SetFromPointAndNormal(rVector3::BackwardVector * scale, rVector3::ForwardVector);
	f.pFar.SetFromPointAndNormal(rVector3::ForwardVector * scale, rVector3::BackwardVector);
	f.pLeft.SetFromPointAndNormal(rVector3::LeftVector * scale, rVector3::RightVector);
	f.pRight.SetFromPointAndNormal(rVector3::RightVector * scale, rVector3::LeftVector);
	f.pTop.SetFromPointAndNormal(rVector3::UpVector * scale, rVector3::DownVector);
	f.pBottom.SetFromPointAndNormal(rVector3::DownVector * scale, rVector3::UpVector);

	EXPECT_TRUE(f.PointInFrustrum(rVector3::ZeroVector));
	EXPECT_TRUE(f.PointInFrustrum(rVector3(1,-1,-1)));

	EXPECT_FALSE(f.PointInFrustrum(rVector3(1,1000,0)));
}
