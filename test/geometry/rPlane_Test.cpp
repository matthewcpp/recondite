#include "gtest/gtest.h"

#include "rPlane.hpp"

class Geometry_rPlane : public ::testing::Test{
};

TEST(Geometry_rPlane, PointDistance){
	rPlane p(1,0,0,1);

	float distance = p.DistanceToPoint(rVector3(-1,0,0));

	EXPECT_FLOAT_EQ(distance, -2.0f);

	distance = p.DistanceToPoint(rVector3(1,0,0));

	EXPECT_FLOAT_EQ(distance, 0.0f);

	distance = p.DistanceToPoint(rVector3(2,0,0));

	EXPECT_FLOAT_EQ(distance, 1.0f);
}

TEST(Geometry_rPlane, Side){
	rPlane p(1,0,0,1);

	int side = p.Side(rVector3(-1,0,0));

	EXPECT_EQ(side, -1);

	side = p.Side(rVector3(1,0,0));

	EXPECT_EQ(side, 0);

	side = p.Side(rVector3(2,0,0));

	EXPECT_EQ(side, 1);
}