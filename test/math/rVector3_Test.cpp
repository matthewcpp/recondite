#include "gtest/gtest.h"
#include "rVector3.hpp"

class Math_rVector3 : public ::testing::Test{
};

TEST(Math_rVector3, Set) {
  rVector3 v;
  v.Set(10.0f, 20.0f, 30.0f);
  
  EXPECT_EQ(v.x, 10.0f);
  EXPECT_EQ(v.y, 20.0f);
  EXPECT_EQ(v.z, 30.0f);
}

TEST(Math_rVector3, AdditionOperator){
	rVector3 v1(10.0f,20.0f,30.0f);
	rVector3 v2(-20.0f, 50.0f, 75.0f);

	rVector3 result = v1 + v2;

	EXPECT_EQ(result.x, -10.0f);
	EXPECT_EQ(result.y, 70.0f);
	EXPECT_EQ(result.z, 105.0f);
}

TEST(Math_rVector3, AdditionWithAssignmentOperator){
	rVector3 v1(10.0f,20.0f,30.0f);
	rVector3 v2(-20.0f, 50.0f, 75.0f);

	v1 += v2;

	EXPECT_EQ(v1.x, -10.0f);
	EXPECT_EQ(v1.y, 70.0f);
	EXPECT_EQ(v1.z, 105.0f);
}

TEST(Math_rVector3, SubtractionOperator){
	rVector3 v1(10.0f,20.0f,30.0f);
	rVector3 v2(-20.0f, 50.0f, 75.0f);

	rVector3 result = v1 - v2;

	EXPECT_EQ(result.x, 30.0f);
	EXPECT_EQ(result.y, -30.0f);
	EXPECT_EQ(result.z, -45.0f);
}

TEST(Math_rVector3, SubtractionWithAssignmentOperator){
	rVector3 v1(10.0f,20.0f,30.0f);
	rVector3 v2(-20.0f, 50.0f, 75.0f);

	v1 -= v2;

	EXPECT_EQ(v1.x, 30.0f);
	EXPECT_EQ(v1.y, -30.0f);
	EXPECT_EQ(v1.z, -45.0f);
}

TEST(Math_rVector3, ScaleOperator){
	rVector3 v(10.0f,20.0f,30.0f);

	rVector3 result = v * 4.0f;

	EXPECT_EQ(result.x, 40.0f);
	EXPECT_EQ(result.y, 80.0f);
	EXPECT_EQ(result.z, 120.0f);
}

TEST(Math_rVector3, ScaleWithAssignmentOperator){
	rVector3 v(10.0f,20.0f,30.0f);

	v *= 4.0f;

	EXPECT_EQ(v.x, 40.0f);
	EXPECT_EQ(v.y, 80.0f);
	EXPECT_EQ(v.z, 120.0f);
}

TEST(Math_rVector3, DivisionOperator){
	rVector3 v(10.0f,20.0f,30.0f);

	rVector3 result = v / 4.0f;

	EXPECT_EQ(result.x, 2.5f);
	EXPECT_EQ(result.y, 5.0f);
	EXPECT_EQ(result.z, 7.5f);
}

TEST(Math_rVector3, DivisionWithAssignmentOperator){
	rVector3 v(10.0f,20.0f,30.0f);

	v /= 4.0f;

	EXPECT_EQ(v.x, 2.5f);
	EXPECT_EQ(v.y, 5.0f);
	EXPECT_EQ(v.z, 7.5f);
}

TEST(Math_rVector3, EqualityOperator){
	rVector3 v1(10.0f,20.0f,30.0f);
	rVector3 v2(10.0f,20.0f,30.0f);
	rVector3 v3(100.0f,200.0f,300.0f);

	EXPECT_TRUE(v1 == v2);
	EXPECT_FALSE(v1 == v3);
}

TEST(Math_rVector3, NotEqualOperator){
	rVector3 v1(10.0f,20.0f,30.0f);
	rVector3 v2(10.0f,20.0f,30.0f);
	rVector3 v3(100.0f,200.0f,300.0f);

	EXPECT_FALSE(v1 != v2);
	EXPECT_TRUE(v1 != v3);
}

TEST(Math_rVector3, Distance){
	rVector3 v1(10.0f, -90.0f, 30.0f);
	rVector3 v2(100.0f, 250.0f, -54.0f);

	float distance = v1.Distance(v2);

	EXPECT_FLOAT_EQ(361.602f, distance);
}

TEST(Math_rVector3, DistanceSquared){
	rVector3 v1(10.0f, -90.0f, 30.0f);
	rVector3 v2(100.0f, 250.0f, -54.0f);

	float distance = v1.DistanceSquared(v2);

	EXPECT_FLOAT_EQ(130756.0064f, distance);
}

TEST(Math_rVector3, Length){
	rVector3 v(3.0f, 2.0f, -1.0f);

	float length = v.Length();

	EXPECT_FLOAT_EQ(3.741657f, length);
}
TEST(Math_rVector3, LengthSquared){
	rVector3 v(3.0f, 2.0f, -1.0f);

	float length = v.LengthSquared();

	EXPECT_FLOAT_EQ(14.0000f, length);
}


