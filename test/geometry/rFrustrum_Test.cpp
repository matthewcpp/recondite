#include "gtest/gtest.h"

#include "rFrustrum.hpp"

class Geometry_rFrustrum : public ::testing::Test{
};

TEST(Geometry_rFrustrum, PointInPlane){
	rFrustrum f;
	f.near.Set(rVector3::ForwardVector, 10);
	f.far.Set(rVector3::BackwardVector, 10);
	f.top.Set(rVector3::DownVector, 10);
	f.bottom.Set(rVector3::UpVector, 10);
	f.left.Set(rVector3::RightVector, 10);
	f.right.Set(rVector3::LeftVector, 10);

	EXPECT_TRUE(f.PointInFrustrum(rVector3::ZeroVector));
	EXPECT_FALSE(f.PointInFrustrum(rVector3(100,0,0)));
}
