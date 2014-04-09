#include "gtest/gtest.h"
#include "rQuaternion.hpp"

class Math_rQuaternion : public ::testing::Test{
};

TEST(Math_rQuaternion, TransformVector3){
	rQuaternion q(0,180,0);

	rVector3 v = rVector3::ForwardVector;
	q.TransformVector3(v);

	//EXPECT_FLOAT_EQ(v.x, 0.0f);
	//EXPECT_FLOAT_EQ(v.y, 0.0f);
	EXPECT_FLOAT_EQ(v.z, 1.0f);
}

TEST(Math_rQuaternion, Identity){
	rVector3 test1(10,10,10);
	rVector3 test2 = test1;

	rQuaternion::Identity.TransformVector3(test1);

	EXPECT_FLOAT_EQ(test1.x, test2.x);
	EXPECT_FLOAT_EQ(test1.y, test2.y);
	EXPECT_FLOAT_EQ(test1.z, test2.z);
}