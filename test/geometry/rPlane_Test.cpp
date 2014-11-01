#include <cmath>

#include "gtest/gtest.h"

#include "rPlane.hpp"

class Geometry_rPlane : public ::testing::Test{
};

TEST(Geometry_rPlane, PointDistanceABCD){
	rVector3 pt(3,1,-2);
	rPlane p1(2,1,-1, 1);
	p1.Normalize();

	float d1 = p1.DistanceToPoint(pt);

	EXPECT_FLOAT_EQ(d1, 10.0f / std::sqrt(6.0f));

	rPlane p2(0,2,0,-3);
	p2.Normalize();

	float d2 = p2.DistanceToPoint(pt);
	EXPECT_FLOAT_EQ(std::fabs(d2), 1.0f / 2.0f);
}

TEST(Geometry_rPlane, PointDistancePtNormal){
	rVector3 planePoint = rVector3::RightVector * 3.0f;
	rPlane p(planePoint, rVector3::RightVector);

	float distance = p.DistanceToPoint(rVector3::ZeroVector);
	EXPECT_FLOAT_EQ(distance, -3.0f);

	planePoint.y = 700.0f;
	p.SetFromPointAndNormal(planePoint,rVector3::RightVector);

	distance = p.DistanceToPoint(rVector3::ZeroVector);
	EXPECT_FLOAT_EQ(distance, -3.0f);

	distance = p.DistanceToPoint(rVector3(-1000,1000,-1000));
	EXPECT_FLOAT_EQ(distance, -1003.0f);

	rPlane p3(rVector3(0,7,0), rVector3::UpVector);
	float d3 = p3.DistanceToPoint(rVector3::ZeroVector);
	EXPECT_FLOAT_EQ(d3, -7.0f);
}

TEST(Geometry_rPlane, Side){
	rPlane p(rVector3::ZeroVector, rVector3::DownVector);

	int side = p.Side(rVector3(0,1,0));
	EXPECT_EQ(side, -1);

	side = p.Side(rVector3(0,-1,0));
	EXPECT_EQ(side, 1);

	side = p.Side(rVector3::ZeroVector);
	EXPECT_EQ(side, 0);
}