#include "gtest/gtest.h"
#include "rVector3.hpp"

class rVector3Test : public ::testing::Test{
};

TEST(rVector3Test, Set) {
  rVector3 v;
  v.Set(10.0f, 20.0f, 30.0f);
  
  EXPECT_EQ(v.x, 10.0f);
  EXPECT_EQ(v.y, 20.0f);
  EXPECT_EQ(v.z, 30.0f);
}

TEST(rVector3Test, AdditionOperator){
	rVector3 v1(10.0f,20.0f,30.0f);
	rVector3 v2(-20.0f, 50.0f, 75.0f);

	rVector3 result = v1 + v2;

	EXPECT_EQ(result.x, -10.0f);
	EXPECT_EQ(result.y, 70.0f);
	EXPECT_EQ(result.z, 105.0f);
}

TEST(rVector3Test, AdditionWithAssignmentOperator){
	rVector3 v1(10.0f,20.0f,30.0f);
	rVector3 v2(-20.0f, 50.0f, 75.0f);

	v1 += v2;

	EXPECT_EQ(v1.x, -10.0f);
	EXPECT_EQ(v1.y, 70.0f);
	EXPECT_EQ(v1.z, 105.0f);
}

TEST(rVector3Test, SubtractionOperator){
	rVector3 v1(10.0f,20.0f,30.0f);
	rVector3 v2(-20.0f, 50.0f, 75.0f);

	rVector3 result = v1 - v2;

	EXPECT_EQ(result.x, 30.0f);
	EXPECT_EQ(result.y, -30.0f);
	EXPECT_EQ(result.z, -45.0f);
}

TEST(rVector3Test, SubtractionWithAssignmentOperator){
	rVector3 v1(10.0f,20.0f,30.0f);
	rVector3 v2(-20.0f, 50.0f, 75.0f);

	v1 -= v2;

	EXPECT_EQ(v1.x, 30.0f);
	EXPECT_EQ(v1.y, -30.0f);
	EXPECT_EQ(v1.z, -45.0f);
}

TEST(rVector3Test, ScaleOperator){
	rVector3 v(10.0f,20.0f,30.0f);

	rVector3 result = v * 4.0f;

	EXPECT_EQ(result.x, 40.0f);
	EXPECT_EQ(result.y, 80.0f);
	EXPECT_EQ(result.z, 120.0f);
}

TEST(rVector3Test, ScaleWithAssignmentOperator){
	rVector3 v(10.0f,20.0f,30.0f);

	v *= 4.0f;

	EXPECT_EQ(v.x, 40.0f);
	EXPECT_EQ(v.y, 80.0f);
	EXPECT_EQ(v.z, 120.0f);
}

TEST(rVector3Test, DivisionOperator){
	rVector3 v(10.0f,20.0f,30.0f);

	rVector3 result = v / 4.0f;

	EXPECT_EQ(result.x, 2.5f);
	EXPECT_EQ(result.y, 5.0f);
	EXPECT_EQ(result.z, 7.5f);
}

TEST(rVector3Test, DivisionWithAssignmentOperator){
	rVector3 v(10.0f,20.0f,30.0f);

	v /= 4.0f;

	EXPECT_EQ(v.x, 2.5f);
	EXPECT_EQ(v.y, 5.0f);
	EXPECT_EQ(v.z, 7.5f);
}

TEST(rVector3Test, EqualityOperator){
	rVector3 v1(10.0f,20.0f,30.0f);
	rVector3 v2(10.0f,20.0f,30.0f);
	rVector3 v3(100.0f,200.0f,300.0f);

	EXPECT_TRUE(v1 == v2);
	EXPECT_FALSE(v1 == v3);
}

TEST(rVector3Test, NotEqualOperator){
	rVector3 v1(10.0f,20.0f,30.0f);
	rVector3 v2(10.0f,20.0f,30.0f);
	rVector3 v3(100.0f,200.0f,300.0f);

	EXPECT_FALSE(v1 != v2);
	EXPECT_TRUE(v1 != v3);
}

TEST(rVector3Test, Distance){
	rVector3 v1(10.0f, -90.0f, 30.0f);
	rVector3 v2(100.0f, 250.0f, -54.0f);

	float distance = v1.Distance(v2);

	EXPECT_FLOAT_EQ(361.602f, distance);
}

TEST(rVector3Test, DistanceSquared){
	rVector3 v1(10.0f, -90.0f, 30.0f);
	rVector3 v2(100.0f, 250.0f, -54.0f);

	float distance = v1.DistanceSquared(v2);

	EXPECT_FLOAT_EQ(130756.0064f, distance);
}

TEST(rVector3Test, Length){
	rVector3 v(3.0f, 2.0f, -1.0f);

	float length = v.Length();

	EXPECT_FLOAT_EQ(3.741657f, length);
}
TEST(rVector3Test, LengthSquared){
	rVector3 v(3.0f, 2.0f, -1.0f);

	float length = v.LengthSquared();

	EXPECT_FLOAT_EQ(14.0000f, length);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}